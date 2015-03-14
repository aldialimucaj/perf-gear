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

    pg_m_item_t item2 = pg_create_measurement_item();
    result = pg_ll_add(item2);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
    size = pg_ll_get_size();
    CU_ASSERT_EQUAL(size, 2);

    pg_m_item_t same_item2 = pg_ll_pop();
    CU_ASSERT_PTR_EQUAL(item2, same_item2);

    pg_m_item_t same_item = pg_ll_pop();
    CU_ASSERT_PTR_EQUAL(item, same_item);

    size = pg_ll_get_size();
    CU_ASSERT_EQUAL(size, 0);
    result = pg_destroy_measurement_item(item);
    result = pg_destroy_measurement_item(item2);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
}

void test_pg_ll_get() {
    pg_err_t result = pg_ll_add(NULL);
    CU_ASSERT_EQUAL(result, PG_ERR_NO_MEASUREMENT);
    long size = pg_ll_get_size();
    CU_ASSERT_EQUAL(size, 0);

    pg_m_item_t item = pg_create_measurement_item();
    item->path = strdup("test/item/one");
    result = pg_ll_add(item);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
    size = pg_ll_get_size();
    CU_ASSERT_EQUAL(size, 1);

    pg_m_item_t item2 = pg_create_measurement_item();
    item2->path = strdup("test/item/two");
    result = pg_ll_add(item2);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
    size = pg_ll_get_size();
    CU_ASSERT_EQUAL(size, 2);

    pg_m_item_t get_item1 = pg_ll_get("test/item/one");
    CU_ASSERT_PTR_EQUAL(item, get_item1);

    pg_m_item_t get_item2 = pg_ll_get("test/item/two");
    CU_ASSERT_PTR_EQUAL(item2, get_item2);


    pg_m_item_t same_item2 = pg_ll_pop();
    CU_ASSERT_PTR_EQUAL(item2, same_item2);

    pg_m_item_t same_item = pg_ll_pop();
    CU_ASSERT_PTR_EQUAL(item, same_item);

    size = pg_ll_get_size();
    CU_ASSERT_EQUAL(size, 0);
    result = pg_destroy_measurement_item(item);
    result = pg_destroy_measurement_item(item2);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
}

void test_pg_ll_pull() {
    pg_err_t result = pg_ll_add(NULL);
    CU_ASSERT_EQUAL(result, PG_ERR_NO_MEASUREMENT);
    long size = pg_ll_get_size();
    CU_ASSERT_EQUAL(size, 0);

    pg_m_item_t item = pg_create_measurement_item();
    item->path = strdup("test/item/one");
    result = pg_ll_add(item);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
    size = pg_ll_get_size();
    CU_ASSERT_EQUAL(size, 1);

    pg_m_item_t item2 = pg_create_measurement_item();
    item2->path = strdup("test/item/two");
    result = pg_ll_add(item2);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
    size = pg_ll_get_size();
    CU_ASSERT_EQUAL(size, 2);

    pg_m_item_t item3 = pg_create_measurement_item();
    item3->path = strdup("test/item/three");
    result = pg_ll_add(item3);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
    size = pg_ll_get_size();
    CU_ASSERT_EQUAL(size, 3);



    pg_m_item_t same_item2 = pg_ll_pull("test/item/two");
    CU_ASSERT_PTR_EQUAL(item2, same_item2);

    pg_m_item_t same_item = pg_ll_pull("test/item/one");
    CU_ASSERT_PTR_EQUAL(item, same_item);

    pg_m_item_t same_item3 = pg_ll_pull("test/item/three");
    CU_ASSERT_PTR_EQUAL(item3, same_item3);

    size = pg_ll_get_size();
    CU_ASSERT_EQUAL(size, 0);
    result = pg_destroy_measurement_item(item);
    result = pg_destroy_measurement_item(item2);
    result = pg_destroy_measurement_item(item3);
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
    CU_add_test(pSuite, "test_pg_ll_get", test_pg_ll_get);
    CU_add_test(pSuite, "test_pg_ll_pull", test_pg_ll_pull);


    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
