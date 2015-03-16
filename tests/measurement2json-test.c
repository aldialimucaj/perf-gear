/*
 * File:   measurement2json-test.c
 * Author: a
 *
 * Created on Mar 16, 2015, 6:42:16 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "../src/measurement2json.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_pg_transform_seq_json() {
    pg_mseq_t seq = pg_create_measurement_sequence();
    seq->timestamp = 1;
    seq->value = 2;

    char *json_result = pg_transform_seq_json(seq);
    CU_ASSERT_STRING_EQUAL(json_result, "{timestamp:1,value:2.00}");
    if (json_result) {
        free(json_result);
    }

    int result = pg_destroy_measurement_sequence(seq);
    CU_ASSERT_EQUAL(result, 0);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("measurement2json-test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    CU_add_test(pSuite, "test_pg_transform_seq_json", test_pg_transform_seq_json);


    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
