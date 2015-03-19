/*
 * File:   collector-test.c
 * Author: a
 *
 * Created on Mar 8, 2015, 11:36:43 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "../src/collector.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_pg_start_collecting(void) {
    pg_init_queue();

    char *path = "pg/collector/start_collecting";
    pg_m_item_t m = pg_start_collecting(path, PG_MEASUREMENT_TYPE_HIT);
    CU_ASSERT_PTR_NOT_NULL(m);

    int result = pg_destroy_measurement_item(m);
    CU_ASSERT_EQUAL(result, 0);

    result = pg_destroy_queue();
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_stop_collecting(void) {
    pg_init_queue();

    char *path = "pg/collector/start_collecting";
    pg_m_item_t m = pg_start_collecting(path, PG_MEASUREMENT_TYPE_HIT);
    CU_ASSERT_PTR_NOT_NULL(m);

    int result = pg_stop_collecting(m);
    CU_ASSERT_EQUAL(result, 0);

    int queue_size = pg_get_queue_size();
    CU_ASSERT_EQUAL(queue_size, 1);

    /* destroy queue */
    result = pg_clear_queue();
    CU_ASSERT_EQUAL(result, 1);
    result = pg_destroy_queue();
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_publish_measurement() {
    pg_init_queue();
    
    pg_err_t result = pg_publish_measurement(NULL);
    CU_ASSERT_EQUAL(result, PG_ERR_NO_MEASUREMENT);

    pg_m_item_t m = pg_create_measurement_item();
    m->type = PG_MEASUREMENT_TYPE_HIT;
    result = pg_publish_measurement(m);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
    
    result = pg_destroy_measurement_item(m);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    size_t queue_size = pg_get_queue_size();
    CU_ASSERT_EQUAL(queue_size, 1);

    /* destroy queue */
    result = pg_clear_queue();
    CU_ASSERT_EQUAL(result, 1);
    result = pg_destroy_queue();
    CU_ASSERT_EQUAL(result, 0);
}



void test_pg_increase_hit(void) {
    pg_err_t result = pg_increase_hit(NULL);
    CU_ASSERT_EQUAL(result, PG_ERR_NO_MEASUREMENT);

    pg_m_item_t m = pg_create_measurement_item();
    m->type = PG_MEASUREMENT_TYPE_UNKNOWN;
    result = pg_increase_hit(m);
    CU_ASSERT_EQUAL(result, PG_ERR_WRONG_MEASUREMENT_TYPE);

    m->type = PG_MEASUREMENT_TYPE_HIT;
    result = pg_increase_hit(m);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
    CU_ASSERT_EQUAL(m->hitValue, 1);
    int destroy_res = pg_destroy_measurement_item(m);
    CU_ASSERT_EQUAL(destroy_res, PG_NO_ERROR);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("collector-test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    CU_add_test(pSuite, "test_pg_start_collecting", test_pg_start_collecting);
    CU_add_test(pSuite, "test_pg_stop_collecting", test_pg_stop_collecting);
    CU_add_test(pSuite, "test_pg_publish_measurement", test_pg_publish_measurement);
    CU_add_test(pSuite, "test_pg_increase_hit", test_pg_increase_hit);

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
