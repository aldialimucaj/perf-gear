#include "../lib/duktape.h"
#include "db-measurement.h"

duk_ret_t pg_br_PGMeasurement(duk_context *ctx) {
    return 1;
}

/* ========================================================================= */

duk_ret_t pg_br_publish_measurement(duk_context *ctx){
    duk_push_boolean(ctx, 1); 
    return 1;
}
