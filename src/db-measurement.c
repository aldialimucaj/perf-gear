#include "../lib/duktape.h"
#include "db-measurement.h"

duk_ret_t pg_br_PGMeasurement(duk_context *ctx) {
    if (duk_is_constructor_call(ctx)) {
        pg_mtype_t type = PG_MEASUREMENT_TYPE_UNKNOWN;
        /* check the arguments passed - if none then hit is default */
        duk_push_this(ctx);

        if (duk_is_string(ctx, -2)) {
            const char *typeStr = duk_require_string(ctx, -2);
            if (strcmp(typeStr, "hit") == 0) {
                type = PG_MEASUREMENT_TYPE_HIT;
            } else if (strcmp(typeStr, "time") == 0) {
                type = PG_MEASUREMENT_TYPE_TIME;
            }
            duk_push_string(ctx, typeStr);
            duk_put_prop_string(ctx, -2, "type");
        } else {
            type = PG_MEASUREMENT_TYPE_HIT;
            duk_push_string(ctx, "hit");
            duk_put_prop_string(ctx, -2, "type");
        }

        switch (type) {
            case PG_MEASUREMENT_TYPE_HIT:
                duk_push_int(ctx, 0);
                duk_put_prop_string(ctx, -2, "hitValue");
                break;
            case PG_MEASUREMENT_TYPE_TIME:
                duk_push_array(ctx);
                duk_put_prop_string(ctx, -2, "sequence");
                break;
            default:
                printf("Unknown measurement type. Please check documentation.\n");
        }
    }
    return 1;
}

/* ========================================================================= */

duk_ret_t pg_br_publish_measurement(duk_context *ctx) {
    duk_push_boolean(ctx, 1);
    return 1;
}
