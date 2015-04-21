#include "dukbridge.h"

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

duk_ret_t pg_br_stopPerfGear(duk_context *ctx) {
    pg_err_t e= pg_stop();
    duk_push_number(ctx, e);
    
    return 1;
}


/*
 *  Module initialization
 */

static const duk_function_list_entry perf_gear_funcs[] = {
    { "startPerfGear", pg_br_startPerfGear, DUK_VARARGS},
    { "stopPerfGear", pg_br_stopPerfGear, 0},
    { NULL, NULL, 0 }
};

static const duk_number_list_entry perf_gear_consts[] = {
    { "PG_VERSION", (double) (1 << 0) },
    { NULL, 0.0 }
};

/* Init function name is dukopen_perf_gear. */
duk_ret_t dukopen_perf_gear(duk_context *ctx) {
    duk_push_object(ctx);
    duk_put_function_list(ctx, -1, perf_gear_funcs);
    duk_put_number_list(ctx, -1, perf_gear_consts);

    /* Return value is the module object.  It's up to the caller to decide
     * how to use the value, e.g. write to global object.
     */
    return 1;
}