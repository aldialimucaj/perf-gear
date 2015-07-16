#include "../lib/duktape.h"
#include "db-measurement.h"

duk_ret_t pg_br_Measurement(duk_context *ctx) {
    if (duk_is_constructor_call(ctx)) {
        /* check the arguments passed - if none then hit is default */
        duk_push_this(ctx);

        if (duk_is_string(ctx, -2)) {
            const char *nameStr = duk_require_string(ctx, -2);
            duk_push_string(ctx, nameStr);
            duk_put_prop_string(ctx, -2, "name");
        } else {
            printf("You must specify a unique name for this measurement. Please check documentation.\n");
        }

        duk_push_int(ctx, 0);
        duk_put_prop_string(ctx, -2, "typeId");
        duk_push_string(ctx, "TYPE_UNKNOWN");
        duk_put_prop_string(ctx, -2, "type");
        duk_push_int(ctx, 0);
        duk_put_prop_string(ctx, -2, "hitValue");
        duk_push_array(ctx);
        duk_put_prop_string(ctx, -2, "sequence");
    }

    return 1;
}

/* ========================================================================= */

duk_ret_t pg_br_measurement_hit(duk_context *ctx) {
    duk_push_this(ctx);
    /* at this point the type is set to 1 = HIT_COUNTER */
    duk_push_int(ctx, 1);
    duk_put_prop_string(ctx, -2, "typeId");
    /* get the value of the counter */
    duk_get_prop_string(ctx, -1, "hitValue");
    int v = duk_require_int(ctx, -1);
    duk_pop(ctx);
    duk_push_int(ctx, ++v);
    duk_put_prop_string(ctx, -2, "hitValue");

    return 0;
}

/* ========================================================================= */

duk_ret_t pg_br_measurement_save_timestamp(duk_context *ctx) {
    duk_push_this(ctx);
    /* if string argument was passed → its the tag */
    const char *tagStr = NULL;
    if (duk_is_string(ctx, -2)) {
        tagStr = duk_require_string(ctx, -2);
    } 
    /* at this point the type is set to 2 = TIME */
    duk_push_int(ctx, 2);
    duk_put_prop_string(ctx, -2, "typeId");
    duk_push_string(ctx, "TIME");
    duk_put_prop_string(ctx, -2, "type");

    /* get the array */
    duk_get_prop_string(ctx, -1, "sequence");
    duk_get_prop_string(ctx, -1, "length");
    int length = duk_require_int(ctx, -1);
    duk_pop(ctx);

    //TODO: set timestamp according to configuration. default microseconds
    unsigned long long timestamp = pg_get_timestamp_usec();
    duk_push_object(ctx);
    duk_push_number(ctx, timestamp);
    duk_put_prop_string(ctx, -2, "timestamp");
    /* add the optional tag */
    if(tagStr){
        duk_push_string(ctx, tagStr);
        duk_put_prop_string(ctx, -2, "tag");
    }
    /* put in array*/
    duk_put_prop_index(ctx, -2, length);

    return 0;
}

/* ========================================================================= */

duk_ret_t pg_br_measurement_publish(duk_context *ctx) {
    duk_push_this(ctx);
    duk_get_prop_string(ctx, -1, "hitValue");
    int v = duk_require_int(ctx, -1);
    duk_pop(ctx);
    duk_get_prop_string(ctx, -1, "typeId");
    int type_id = duk_require_int(ctx, -1);
    duk_pop(ctx);
    duk_get_prop_string(ctx, -1, "name");
    const char *path = duk_require_string(ctx, -1);
    duk_pop(ctx);

    pg_m_item_t *m = pg_new_measurement(path, type_id);

    /* adding dynamic parameters */
    if (m) {
        pg_br_msrt_add_params(ctx, m);
    }

    switch (type_id) {
        case 1: // type = HIT
            m->hitValue = v;
            break;
        case 2: // type = TIME
        {
            duk_get_prop_string(ctx, -1, "sequence");
            duk_enum(ctx, -1, DUK_ENUM_SORT_ARRAY_INDICES);
            while (duk_next(ctx, -1, 1)) {
                duk_get_prop_string(ctx, -1, "timestamp");
                size_t ts_value = (size_t) duk_require_number(ctx, -1);
                /* pop number:timestamp */
                duk_pop(ctx);
                pg_mseq_t *seq = pg_create_measurement_sequence();
                seq->timestamp = ts_value;
                seq->value = 0;
                duk_get_prop_string(ctx, -1, "tag");
                if(duk_is_string(ctx, -1)) seq->tag = PG_STRDUP(duk_get_string(ctx, -1));
                /* pop string:tag */
                duk_pop(ctx);

                pg_add_measurement_sequence(m, seq);

                /* pop duk_next (key, value) */
                duk_pop_2(ctx);
            }

            duk_pop(ctx); /* pop enum object */
            break;
        }
        default:
            printf("You are publishing an undefined measurement\n");
    }

    //TODO: sequences need special case

    /* publish */
    pg_err_t result = pg_publish_measurement(m);
    /* publishing creates a copy we need to delete this one */
    pg_err_t r_destroy = pg_destroy_measurement_item(m);

    if (result == PG_NO_ERROR && r_destroy == PG_NO_ERROR) {
        duk_push_boolean(ctx, 1); // true
    } else {
        duk_push_boolean(ctx, 0); // false
    }


    return 1;
}

/* ========================================================================= */
pg_err_t pg_br_msrt_add_params(duk_context *ctx, pg_m_item_t *m) {
    if (!m) return PG_ERR_BAD_ARG;
    duk_enum(ctx, -1, DUK_ENUM_INCLUDE_INTERNAL);
    while (duk_next(ctx, -1, 1)) {
        const char *param_key = duk_require_string(ctx, -2);
        if (!strcmp(param_key, "name") || !strcmp(param_key, "hitValue") ||
                !strcmp(param_key, "typeId")) {
            duk_pop_2(ctx); /* pop key/value */
            continue;
        }
        if (duk_is_string(ctx, -1)) {
            const char *key = duk_require_string(ctx, -2);
            const char *value = duk_require_string(ctx, -1);
            pg_msrt_add_param_str(m, key, value);
            //m->hitValue = 5;
            //if (strcmp(key, value)) m->hitValue = 1;
        }
        duk_pop_2(ctx); /* pop key/value */
    }
    duk_pop(ctx); /* pop enum object */

    return PG_NO_ERROR;
}