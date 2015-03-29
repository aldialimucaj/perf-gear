/*
 * File:   measurement2json-test.c
 * Author: Aldi Alimucaj
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

void test_pg_m2j_transform() {
    pg_m_item_t *m = pg_create_measurement_item();
    m->path = strdup("test/func/one");
    m->type = PG_MEASUREMENT_TYPE_HIT;
    m->hitValue = 11;

    char *json_result = pg_m2j_transform(m);
    const char *cmp_m_str = "{\"path\":\"test/func/one\",\"type\":1,\"hitValue\":11,\"sequence\":[]}";
    CU_ASSERT_STRING_EQUAL(json_result, cmp_m_str);
    if (json_result) {
        free(json_result);
    }
    
    pg_mseq_t *seq = pg_create_measurement_sequence();
    seq->timestamp = 3425;
    seq->value = 624352;
    m->sequence = seq;
    
    json_result = pg_m2j_transform(m);
    const char *cmp_m_str2 = "{\"path\":\"test/func/one\",\"type\":1,\"hitValue\":11,\"sequence\":[{\"timestamp\":3425,\"value\":624352.00}]}";
    CU_ASSERT_STRING_EQUAL(json_result, cmp_m_str2);
    if (json_result) {
        free(json_result);
    }
    
    pg_mseq_t *seq2 = pg_create_measurement_sequence();
    seq2->timestamp = 8563;
    seq2->value = 4254;
    seq->next = seq2;
    
    json_result = pg_m2j_transform(m);
    const char *cmp_m_str3 = "{\"path\":\"test/func/one\",\"type\":1,\"hitValue\":11,\"sequence\":[{\"timestamp\":3425,\"value\":624352.00},{\"timestamp\":8563,\"value\":4254.00}]}";
    CU_ASSERT_STRING_EQUAL(json_result, cmp_m_str3);
    if (json_result) {
        free(json_result);
    }
    
    int result = pg_destroy_measurement_item(m);
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_transform_seq_json() {
    pg_mseq_t *seq = pg_create_measurement_sequence();
    seq->timestamp = 1;
    seq->value = 2;

    char *json_result = pg_transform_seq_json(seq);
    CU_ASSERT_STRING_EQUAL(json_result, "{\"timestamp\":1,\"value\":2.00}");
    if (json_result) {
        free(json_result);
    }

    int result = pg_destroy_measurement_sequence(seq);
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_m2j_seq2json_array() {
    char *null_array = pg_m2j_seq2json_array(NULL);
    CU_ASSERT_PTR_NULL(null_array);

    pg_m_item_t *m = pg_create_measurement_item();
    char *empty_array = pg_m2j_seq2json_array(m);
    CU_ASSERT_STRING_EQUAL(empty_array, "[]");
    if (empty_array) free(empty_array);

    pg_mseq_t *seq = pg_create_measurement_sequence();
    seq->timestamp = 1;
    seq->value = 2;
    m->sequence = seq;

    char *seq_array = pg_m2j_seq2json_array(m);
    CU_ASSERT_STRING_EQUAL(seq_array, "[{\"timestamp\":1,\"value\":2.00}]");
    if (seq_array) free(seq_array);

    pg_mseq_t *seq2 = pg_create_measurement_sequence();
    seq2->timestamp = 2;
    seq2->value = 3;
    seq->next = seq2;

    char *seq_array2 = pg_m2j_seq2json_array(m);
    CU_ASSERT_STRING_EQUAL(seq_array2, "[{\"timestamp\":1,\"value\":2.00},{\"timestamp\":2,\"value\":3.00}]");
    if (seq_array2) free(seq_array2);

    int result = pg_destroy_measurement_item(m);
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
    CU_add_test(pSuite, "test_pg_m2j_seq2json_array", test_pg_m2j_seq2json_array);
    CU_add_test(pSuite, "test_pg_m2j_transform", test_pg_m2j_transform);


    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
