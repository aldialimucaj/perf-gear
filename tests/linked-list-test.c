/*
 * File:   linked-list-test.c
 * Author: Aldi Alimucaj
 *
 * Created on Mar 10, 2015, 2:51:33 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "../src/linked-list.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_pg_ll_create() {
    pg_ll_item_t item = pg_ll_create();
    CU_ASSERT_PTR_NOT_NULL(item);
    pg_err_t result = pg_ll_destroy(item);
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_ll_add() {
    pg_err_t result = pg_ll_add(NULL);
    CU_ASSERT_EQUAL(result, PG_ERR_NO_MEASUREMENT);
    long size = pg_ll_get_size();
    CU_ASSERT_EQUAL(size, 0);
    pg_m_item_t item = pg_create_measurement_item();
    result = pg_ll_add(item);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
    size = pg_ll_get_size();
    CU_ASSERT_EQUAL(size, 1);
    pg_m_item_t same_item = pg_ll_pop();
    CU_ASSERT_PTR_EQUAL(item, same_item);
    size = pg_ll_get_size();
    CU_ASSERT_EQUAL(size, 0);
    result = pg_destroy_measurement_item(item);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("linked-list-test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    CU_add_test(pSuite, "test_pg_ll_create", test_pg_ll_create);
    CU_add_test(pSuite, "test_pg_ll_add", test_pg_ll_add);


    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
