#include "dukbridge.h"
#include "db-measurement.h"

duk_ret_t pg_br_startPerfGear(duk_context *ctx) {
    duk_push_this(ctx);
    duk_get_prop_string(ctx, -1, "config");

    duk_get_prop_string(ctx, -1, "folder");
    const char* folder = NULL;
    if (!duk_is_undefined(ctx, -1)) {
        folder = duk_to_string(ctx, -1);
    }
    /* pop string:folder */
    duk_pop(ctx);

    duk_get_prop_string(ctx, -1, "url");
    const char* url = NULL;
    if (!duk_is_undefined(ctx, -1)) {
        url = duk_to_string(ctx, -1);
    }
    /* pop string:url */
    duk_pop(ctx);
    /* pop obj:config */
    duk_pop(ctx);

    pg_config_t* c = pg_create_config();

    if (folder) c->folder = PG_STRDUP(folder);
    if (url) c->url = PG_STRDUP(url);
    c->repeat = 100;

    pg_err_t e = pg_start(c);
    if (e == PG_NO_ERROR) {
        duk_push_boolean(ctx, 1); // true
        duk_put_prop_string(ctx, -2, "started");
    }
    duk_push_number(ctx, e);

    pg_destroy_config(c);

    return 1;
}

/* ========================================================================= */

duk_ret_t pg_br_stopPerfGear(duk_context *ctx) {
    pg_err_t e = pg_stop();
    duk_push_this(ctx);
    if (e == PG_NO_ERROR) {
        duk_push_boolean(ctx, 0); // false
        duk_put_prop_string(ctx, -2, "started");
    }
    duk_push_number(ctx, e);

    return 1;
}

/* ========================================================================= */

duk_ret_t pg_br_PerfGear(duk_context *ctx) {
    if (duk_is_constructor_call(ctx)) {
        duk_push_this(ctx);
        if (duk_is_object(ctx, -2)) {
            duk_dup(ctx, -2);
            duk_put_prop_string(ctx, -2, "config");
        }
    }

    return 1;
}

/* ========================================================================= */

pg_err_t dukopen_perf_gear(duk_context *ctx) {
    /* global object */
    duk_push_global_object(ctx);

    /* adding PerfGear object */
    duk_push_c_function(ctx, pg_br_PerfGear, 1);
    duk_push_object(ctx);

    duk_push_c_function(ctx, pg_br_startPerfGear, 0);
    duk_put_prop_string(ctx, -2, "start");

    duk_push_c_function(ctx, pg_br_stopPerfGear, 0);
    duk_put_prop_string(ctx, -2, "stop");

    duk_put_prop_string(ctx, -2, "prototype");

    duk_put_prop_string(ctx, -2, PERF_GEAR_OBJ_NAME);


    /* adding PGMeasurement object */
    duk_push_c_function(ctx, pg_br_Measurement, 1);
    duk_push_object(ctx);

    duk_push_c_function(ctx, pg_br_measurement_publish, 0);
    duk_put_prop_string(ctx, -2, "publish");

    duk_push_c_function(ctx, pg_br_measurement_hit, 0);
    duk_put_prop_string(ctx, -2, "hit");

    duk_push_c_function(ctx, pg_br_measurement_save_timestamp, 0);
    duk_put_prop_string(ctx, -2, "saveTimestamp");

    duk_put_prop_string(ctx, -2, "prototype");

    duk_put_prop_string(ctx, -2, MEASUREMNET_OBJ_NAME);

    /* remove global from stack */
    duk_pop(ctx);

    return PG_NO_ERROR;
}
