#include "dukbridge.h"

void pg_say_hello(duk_context *ctx) {

    duk_eval_string(ctx, "print('Hello world!');");


    duk_push_global_object(ctx);
    duk_push_c_function(ctx, adder, DUK_VARARGS);
    duk_put_prop_string(ctx, -2 /*idx:global*/, "adder");
    duk_pop(ctx); /* pop global */

    duk_eval_string(ctx, "print('2+4=' + adder(2, 4));");
    duk_pop(ctx); /* pop eval result */


}

int adder(duk_context *ctx) {
    int i;
    int n = duk_get_top(ctx); /* #args */
    double res = 0.0;

    for (i = 0; i < n; i++) {
        res += duk_to_number(ctx, i);
    }

    duk_push_number(ctx, res);
    return 1; /* one return value */
}

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

pg_err_t pg_br_register_functions(duk_context *ctx) {
    duk_idx_t r = 0;
    duk_bool_t g = 0;

    // ---
    r = duk_push_c_function(ctx, pg_br_startPerfGear, DUK_VARARGS);
    if (r < 0) return PG_ERR_REGISTER_FUNC;
    g = duk_put_prop_string(ctx, -2, "startPerfGear");
    duk_pop(ctx); /* ignore result */
    // ---


    return PG_NO_ERROR;
}