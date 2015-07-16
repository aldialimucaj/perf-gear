/*
 * File:   dispatcher-test.c
 * Author: Aldi Alimucaj
 *
 * Created on Mar 18, 2015, 8:17:38 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "../src/dispatcher.h"
#include "../src/measurement2json.h"

#define PG_DSP_TEST_URL "http://localhost:3000/api/measurements"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}



pg_m_item_t* get_measurement_test() {
    pg_m_item_t *m = pg_create_measurement_item();
    m->path = strdup("test/dsp/measurement/1");
    m->type = PG_MEASUREMENT_TYPE_HIT;
    m->hitValue = 11;

    pg_mseq_t *seq = pg_create_measurement_sequence();
    seq->timestamp = 3425;
    seq->value = 624352;
    m->sequence = seq;

    pg_mseq_t *seq2 = pg_create_measurement_sequence();
    seq2->timestamp = 8563;
    seq2->value = 4254;
    seq->next = seq2;

    return m;
}

char* get_measurement_test_content() {
    pg_m_item_t *m = get_measurement_test();

    char *json_result = pg_m2j_transform(m);

    int result = pg_destroy_measurement_item(m);
    CU_ASSERT_EQUAL(result, 0);

    return json_result;
}

void test_pg_dsp_persist() {
    pg_config_t *config = pg_create_config();
    config->folder = PG_STRDUP("/tmp/pg_dst/t1.json");
    
    pg_m_item_t *m = get_measurement_test();
    pg_err_t err = pg_dsp_persist(config, m);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
    
    config->url = PG_STRDUP(PG_DSP_TEST_URL);
    err = pg_dsp_persist(config, m);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
    
    int result = pg_destroy_measurement_item(m);
    CU_ASSERT_EQUAL(result, 0);
    
    err = pg_destroy_config(config);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
}


void test_pg_dsp_save_to_disk() {
    pg_err_t err = pg_dsp_save_to_disk(NULL, NULL);
    CU_ASSERT_EQUAL(err, PG_ERR_NO_DES_PATH);
    
    err = pg_dsp_save_to_disk("/tmp/f1.json", NULL);
    CU_ASSERT_EQUAL(err, PG_ERR_NO_CONTENT);
    
    err = pg_dsp_save_to_disk("/root/f1.json", "noop");
    CU_ASSERT_EQUAL(err, PG_ERR_COULD_NOT_OPEN_PATH);
    
    char *json_result = get_measurement_test_content();
    err = pg_dsp_save_to_disk("/tmp/f1.json", json_result);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
    if (json_result) free(json_result);

}

void test_pg_dsp_net_post() {
    pg_err_t err = pg_dsp_net_post(PG_DSP_TEST_URL, "{\"key\":\"value\"}");
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("dispatcher-test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    CU_add_test(pSuite, "test_pg_dsp_persist", test_pg_dsp_persist);
    CU_add_test(pSuite, "test_pg_dsp_save_to_disk", test_pg_dsp_save_to_disk);
    CU_add_test(pSuite, "test_pg_dsp_net_post", test_pg_dsp_net_post);

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
