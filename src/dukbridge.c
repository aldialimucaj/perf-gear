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

int pg_br_register_functions(duk_context *ctx) {
    duk_push_c_function(ctx, adder, DUK_VARARGS);
}