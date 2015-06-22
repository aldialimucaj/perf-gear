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

void test_pg_br_PerfGear() {
    duk_context *ctx = duk_create_heap_default();
    // ---
    /* push the constructor */
    duk_push_c_function(ctx, pg_br_PerfGear, 1);
    duk_idx_t obj_idx = duk_push_object(ctx);
    duk_push_string(ctx, "/tmp/pg");
    duk_put_prop_string(ctx, obj_idx, "folder");
    duk_new(ctx, 1);

    duk_get_prop_string(ctx, -1, "config");
    CU_ASSERT(duk_is_object(ctx, -1));
    duk_pop(ctx);
    duk_pop(ctx);
    // ---
    duk_destroy_heap(ctx);
}

void test_pg_br_startPerfGear() {
    duk_context *ctx = duk_create_heap_default();

    // ---
    /* push the constructor */
    duk_push_c_function(ctx, pg_br_PerfGear, 1);
    duk_idx_t obj_idx = duk_push_object(ctx);
    duk_push_string(ctx, "/tmp/pg_db_s");
    duk_put_prop_string(ctx, obj_idx, "folder");
    duk_new(ctx, 1);

    duk_push_c_function(ctx, pg_br_startPerfGear, 0);
    duk_dup(ctx, -2);
    duk_call_method(ctx, 0);

    pg_err_t e = duk_to_number(ctx, -1);
    CU_ASSERT_EQUAL(e, PG_NO_ERROR);
    duk_pop(ctx); /* ignore result */
    // ---
    duk_destroy_heap(ctx);
    pg_stop();
}

void test_pg_br_stopPerfGear() {
    duk_context *ctx = duk_create_heap_default();

    duk_push_c_function(ctx, pg_br_PerfGear, 1);
    duk_idx_t obj_idx = duk_push_object(ctx);
    duk_push_string(ctx, "/tmp/pg_db_s");
    duk_put_prop_string(ctx, obj_idx, "folder");
    duk_new(ctx, 1);

    struct pg_config c = {
        .folder = "/tmp/pg_db",
        .repeat = 10
    };
    pg_start(&c);
    // ---
    duk_push_c_function(ctx, pg_br_stopPerfGear, 0);
    duk_dup(ctx, -2);
    duk_call_method(ctx, 0);

    pg_err_t e = duk_to_number(ctx, -1);
    CU_ASSERT_EQUAL(e, PG_NO_ERROR);
    // ---
    duk_destroy_heap(ctx);
}

void test_dukopen_perf_gear() {
    duk_context *ctx = duk_create_heap_default();
    // ---
    dukopen_perf_gear(ctx);
    duk_push_global_object(ctx);

    duk_get_prop_string(ctx, -1, PERF_GEAR_OBJ_NAME);
    CU_ASSERT_TRUE(duk_is_object(ctx, -1));
    duk_pop(ctx);
    
    duk_get_prop_string(ctx, -1, MEASUREMNET_OBJ_NAME);
    CU_ASSERT_TRUE(duk_is_object(ctx, -1));
    duk_pop(ctx);
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
    CU_add_test(pSuite, "test_pg_br_PerfGear", test_pg_br_PerfGear);
    CU_add_test(pSuite, "test_pg_br_startPerfGear", test_pg_br_startPerfGear);
    CU_add_test(pSuite, "test_pg_br_stopPerfGear", test_pg_br_stopPerfGear);
    CU_add_test(pSuite, "test_dukopen_perf_gear", test_dukopen_perf_gear);

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
