#include "../lib/duktape.h"
#include "db-measurement.h"

duk_ret_t pg_br_PGMeasurement(duk_context *ctx) {
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
    duk_get_prop_string(ctx, -1, "hitValue");
    int v = duk_require_int(ctx, -1);
    duk_pop(ctx);
    duk_push_int(ctx, ++v);
    duk_put_prop_string(ctx, -2, "hitValue");

    return 0;
}

/* ========================================================================= */

duk_ret_t pg_br_measurement_publish(duk_context *ctx) {
    duk_push_boolean(ctx, 1);
    return 1;
}