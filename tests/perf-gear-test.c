/*
 * File:   perf-gear-test.c
 * Author: garmin
 *
 * Created on Mar 19, 2015, 11:46:04 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "../src/perf-gear.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_pg_harvest_measurements(void) {
    pg_init_queue();

    pg_m_item_t m = pg_create_measurement_item();
    m->type = PG_MEASUREMENT_TYPE_HIT;
    m->path = strdup("func1/test/hit");
    pg_err_t result = pg_publish_measurement(m);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    result = pg_destroy_measurement_item(m);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    size_t queue_size = pg_get_queue_size();
    CU_ASSERT_EQUAL(queue_size, 1);

    // ---

    struct pg_config c = {
        .folder = "/tmp/",
        .repeat = 10       
    };
    
    result = pg_harvest_measurements(&c);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    // ---

    /* destroy queue */
    result = pg_clear_queue();
    CU_ASSERT_EQUAL(result, 0);
    result = pg_destroy_queue();
    CU_ASSERT_EQUAL(result, 0);

}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("perf-gear-test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    CU_add_test(pSuite, "test_pg_harvest_measurements", test_pg_harvest_measurements);


    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
