#include "dukbridge.h"

void pg_say_hello(void) {
    duk_context *ctx = duk_create_heap_default();
    duk_eval_string(ctx, "print('Hello world!');");
    duk_destroy_heap(ctx);
}
