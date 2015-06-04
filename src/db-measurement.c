#include "../lib/duktape.h"
#include "db-measurement.h"

duk_ret_t pg_br_Measurement(duk_context *ctx) {
    if (duk_is_constructor_call(ctx)) {
        pg_mtype_t type = PG_MEASUREMENT_TYPE_UNKNOWN;
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
    /* at this point the type is set to 2 = TIME */
    duk_push_int(ctx, 2);
    duk_put_prop_string(ctx, -2, "typeId");

    /* get the array */
    duk_get_prop_string(ctx, -1, "sequence");
    duk_get_prop_string(ctx, -1, "length");
    int length = duk_require_int(ctx, -1);
    duk_pop(ctx);

    unsigned long long timestamp = pg_get_timestamp();
    duk_push_object(ctx);
    duk_push_number(ctx, timestamp);
    duk_put_prop_string(ctx, -2, "timestamp");
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

    pg_m_item_t *m = pg_create_measurement_item();

    m->type = type_id;
    m->path = strdup(path);
    switch (type_id) {
        case 1:
            m->hitValue = v;
            break;
        case 2:
        {
            duk_get_prop_string(ctx, -1, "sequence");
            duk_enum(ctx, -1, DUK_ENUM_SORT_ARRAY_INDICES);
            while (duk_next(ctx, -1, 1)) {
                duk_get_prop_string(ctx, -1, "timestamp");
                size_t ts_value = (size_t) duk_require_number(ctx, -1);
                pg_mseq_t *seq = pg_create_measurement_sequence();
                seq->timestamp = ts_value;
                seq->value = 0;
                pg_add_measurement_sequence(m, seq);
                
                duk_pop_3(ctx);
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
    if (result == PG_NO_ERROR) {
        duk_push_boolean(ctx, 1); // true
    } else {
        duk_push_boolean(ctx, 0); // false
    }

    result = pg_destroy_measurement_item(m);

    return 1;
}
