#include "dukbridge.h"
#include "db-measurement.h"

duk_ret_t pg_br_startPerfGear(duk_context *ctx) {
    duk_json_decode(ctx, -1);
    duk_get_prop_string(ctx, -1, "folder");
    const char* folder = duk_to_string(ctx, -1);

    pg_config_t* c = pg_create_config();

    c->folder = strdup(folder);
    c->repeat = 10;

    pg_err_t e = pg_start(c);
    duk_push_number(ctx, e);

    pg_destroy_config(c);

    return 1;
}

/* ========================================================================= */

duk_ret_t pg_br_stopPerfGear(duk_context *ctx) {
    pg_err_t e = pg_stop();
    duk_push_number(ctx, e);

    return 1;
}

/* ========================================================================= */

duk_ret_t pg_br_PerfGear(duk_context *ctx) {
    if (duk_is_constructor_call(ctx)) {
    }

    return 1;
}

/* ========================================================================= */

duk_ret_t dukopen_perf_gear(duk_context *ctx) {
    /* global object */
    duk_push_global_object(ctx);
    
    /* adding PerfGear object */
    duk_push_c_function(ctx, pg_br_PerfGear, 0);
    duk_push_object(ctx);
    
    duk_push_c_function(ctx, pg_br_startPerfGear, 0);
    duk_put_prop_string(ctx, -2, "startPerfGear");

    duk_push_c_function(ctx, pg_br_stopPerfGear, 0);
    duk_put_prop_string(ctx, -2, "stopPerfGear");

    duk_put_prop_string(ctx, -2, "prototype");

    duk_put_prop_string(ctx, -2, "PerfGear");
    
    
    /* adding PGMeasurement object */
    duk_push_c_function(ctx, pg_br_PGMeasurement, 1);
    duk_push_object(ctx);
    
    duk_push_c_function(ctx, pg_br_publish_measurement, 0);
    duk_put_prop_string(ctx, -2, "publish");   
    
    duk_put_prop_string(ctx, -2, "prototype");

    duk_put_prop_string(ctx, -2, "PGMeasurement");
    
    /* remove global from stack */
    duk_pop(ctx);

    return 0;
}
