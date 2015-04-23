/** @brief Test js files
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../src/perf-gear.h"
#include "../src/dukbridge.h"
#include "../lib/duktape.h"

int main(int argc, const char *argv[]) {
    duk_context *ctx = NULL;
    char line[4096];
    char idx;
    int ch;

    if (argc != 2) {
        printf("Usage: %s [testfile].js\n", argv[0]);
        exit(1);
    }

    FILE *file = fopen( argv[1], "r" );

    if(!file) {
        printf("File >%s< does not exist!\n", argv[1]);
        exit(1);   
    }

    ctx = duk_create_heap_default();
    if (!ctx) {
        printf("Failed to create a Duktape heap.\n");
        exit(1);
    }

    if (duk_peval_file(ctx, argv[1]) != 0) {
        printf("Error: %s\n", duk_safe_to_string(ctx, -1));
        exit(1);
    }
    duk_pop(ctx); /* ignore result */
    
    duk_push_c_function(ctx, dukopen_perf_gear, 0 /*nargs*/);
    duk_call(ctx, 0);
    duk_put_global_string(ctx, "PerfGear");

    duk_destroy_heap(ctx);
}
