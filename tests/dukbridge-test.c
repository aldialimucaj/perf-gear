/*
 * File:   dukbridge-test.c
 * Author: a
 *
 * Created on Apr 1, 2015, 11:16:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "../src/dukbridge.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_pg_br_startPerfGear() {
    /*duk_context *ctx = duk_create_heap_default();
    duk_push_global_object(ctx);
    // ---
    duk_idx_t r = 0;
    duk_bool_t g = 0;
    r = duk_push_c_function(ctx, pg_br_startPerfGear, DUK_VARARGS);
    duk_idx_t obj_idx;
    obj_idx = duk_push_object(ctx);
    duk_push_string(ctx, "/tmp/pg_db");
    duk_put_prop_string(ctx, -2, "folder");
    const char* json = duk_json_encode(ctx, -1);
    CU_ASSERT_STRING_EQUAL(json, "{\"folder\":\"/tmp/pg_db\"}");
    duk_call(ctx, 1);

    pg_err_t e = duk_to_number(ctx, -1);
    CU_ASSERT_EQUAL(e, PG_NO_ERROR);
    duk_pop(ctx); /* ignore result */
    // ---
    /*duk_destroy_heap(ctx);
    pg_stop();*/
}

void test_pg_br_stopPerfGear() {
    duk_context *ctx = duk_create_heap_default();
    duk_push_global_object(ctx);

    struct pg_config c = {
        .folder = "/tmp/pg_db",
        .repeat = 10
    };
    pg_start(&c);
    // ---
    duk_idx_t r = 0;
    duk_bool_t g = 0;
    r = duk_push_c_function(ctx, pg_br_stopPerfGear, DUK_VARARGS);
    duk_call(ctx, 0);

    // ---
    duk_destroy_heap(ctx);
}

void test_pg_br_measurement() {
    //TODO: add tests
}

void test_pg_br_register_functions() {
    duk_context *ctx = duk_create_heap_default();
    // ---
    /* Module loading happens with a Duktape/C call wrapper. */
    duk_push_c_function(ctx, dukopen_perf_gear, 0 /*nargs*/);
    duk_call(ctx, 0);
    duk_put_global_string(ctx, "PerfGear");
    // ---
    duk_destroy_heap(ctx);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("dukbridge-test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    CU_add_test(pSuite, "test_pg_br_register_functions", test_pg_br_register_functions);
    CU_add_test(pSuite, "test_pg_br_startPerfGear", test_pg_br_startPerfGear);
    CU_add_test(pSuite, "test_pg_br_stopPerfGear", test_pg_br_stopPerfGear);
    CU_add_test(pSuite, "test_pg_br_measurement", test_pg_br_measurement);

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
