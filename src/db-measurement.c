#include "../lib/duktape.h"
#include "db-measurement.h"

duk_ret_t pg_br_PGMeasurement(duk_context *ctx) {
    if (duk_is_constructor_call(ctx)) {
        /* check the arguments passed - if none then hit is default */
        duk_push_this(ctx);

        if (duk_is_string(ctx, -2)) {
            duk_push_string(ctx, duk_require_string(ctx, -2));
            duk_put_prop_string(ctx, -2, "type");
        } else {
            duk_push_string(ctx, "hit");
            duk_put_prop_string(ctx, -2, "type");
        }
    }
    return 1;
}

/* ========================================================================= */

duk_ret_t pg_br_publish_measurement(duk_context *ctx) {
    duk_push_boolean(ctx, 1);
    return 1;
}
