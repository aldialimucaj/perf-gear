/*
 * File:   db-measurement-test.c
 * Author: garmin
 *
 * Created on May 29, 2015, 4:23:35 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "../src/db-measurement.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_pg_br_PGMeasurement() {
    duk_context *ctx = NULL;
    ctx = duk_create_heap_default();

    /* push the constructor */
    duk_push_c_function(ctx, pg_br_PGMeasurement, 1);
    /* constructor call without argument */
    duk_new(ctx, 0);
    duk_get_prop_string(ctx, -1, "name");
    CU_ASSERT(duk_is_undefined(ctx, -1));
    duk_pop(ctx);
    duk_pop(ctx);

    /* push the constructor */
    duk_push_c_function(ctx, pg_br_PGMeasurement, 1);
    /* constructor call with argument */
    duk_push_string(ctx, "test/api/constructor");
    duk_new(ctx, 1);

    CU_ASSERT(duk_is_object(ctx, -1));

    duk_get_prop_string(ctx, -1, "name");
    CU_ASSERT_STRING_EQUAL(duk_require_string(ctx, -1), "test/api/constructor");
    duk_pop(ctx);

    duk_get_prop_string(ctx, -1, "type");
    CU_ASSERT_STRING_EQUAL(duk_require_string(ctx, -1), "TYPE_UNKNOWN");
    duk_pop(ctx);

    duk_destroy_heap(ctx);
}

void test_pg_br_publish_measurement() {
    CU_ASSERT(2 * 3 == 6);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("db-measurement-test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    CU_add_test(pSuite, "test_pg_br_PGMeasurement", test_pg_br_PGMeasurement);
    CU_add_test(pSuite, "test_pg_br_publish_measurement", test_pg_br_publish_measurement);


    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
