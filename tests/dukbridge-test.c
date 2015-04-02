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

void test_say_hello() {
    CU_ASSERT_EQUAL(1,1); 
    pg_say_hello();
    CU_ASSERT_EQUAL(1,1); 
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
    CU_add_test(pSuite, "test_say_hello", test_say_hello);

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
