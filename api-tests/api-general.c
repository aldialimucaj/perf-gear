/*
 * File:   api-general.c
 * Author: a
 *
 * Created on Jun 22, 2015, 9:51:22 PM
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

void test_pseudo_main() {
    struct pg_config c = {
        .folder = "/tmp/pg_api"
    };
    pg_err_t err;
    err = pg_start(&c);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    pg_m_item_t* m1 = pg_new_measurement("api/test/pseudo_main", PG_MEASUREMENT_TYPE_HIT);
    CU_ASSERT(m1 != NULL);

    err = pg_increase_hit(m1);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_stop_collecting(m1);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_stop();
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
}

void test_pseudo_main_init() {
    struct pg_config c = {
        .folder = "/tmp/pg_api"
    };
    pg_err_t err;
    err = pg_init();
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    pg_m_item_t* m1 = pg_new_measurement("api/test/pseudo_main/init", PG_MEASUREMENT_TYPE_HIT);
    CU_ASSERT(m1 != NULL);

    err = pg_increase_hit(m1);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_stop_collecting(m1);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_collect(&c);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_stop();
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
}

void test_pseudo_main_loop() {
    struct pg_config c = {
        .folder = "/tmp/pg_api"
    };
    pg_err_t err;
    err = pg_init();
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    pg_m_item_t* m1 = pg_new_measurement("api/test/pseudo_main/loop", PG_MEASUREMENT_TYPE_HIT);
    CU_ASSERT(m1 != NULL);

    for (int i = 0; i < 10000; i++) {
        // doing some stuff here
        err = pg_increase_hit(m1);
        CU_ASSERT_EQUAL(err, PG_NO_ERROR);
    }

    err = pg_stop_collecting(m1);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_collect(&c);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_stop();
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
}

void test_pseudo_main_loop_timestamp() {
    struct pg_config c = {
        .folder = "/tmp/pg_api"
    };
    pg_err_t err;
    err = pg_init();
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    pg_m_item_t* m1 = pg_new_measurement("api/test/pseudo_main/loop/timestamp", PG_MEASUREMENT_TYPE_TIME);
    CU_ASSERT(m1 != NULL);

    for (int i = 0; i < 1000; i++) {
        // doing some stuff here
        err = pg_save_timestamp(m1);
        CU_ASSERT_EQUAL(err, PG_NO_ERROR);
    }

    err = pg_stop_collecting(m1);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_collect(&c);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_stop();
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
}

void test_pseudo_main_loop_timestamp_with_tag() {
    struct pg_config c = {
        .folder = "/tmp/pg_api"
    };
    pg_err_t err;
    err = pg_init();
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    pg_m_item_t* m1 = pg_new_measurement("api/test/pseudo_main/loop/timestamp_wtag", PG_MEASUREMENT_TYPE_TIME);
    CU_ASSERT(m1 != NULL);

    for (int i = 0; i < 1000; i++) {
        // doing some stuff here
        err = pg_save_timestamp_tag(m1, "test-tag");
        CU_ASSERT_EQUAL(err, PG_NO_ERROR);
    }

    err = pg_stop_collecting(m1);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_collect(&c);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_stop();
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
}

void test_pseudo_main_loop_ram_usage() {
    struct pg_config c = {
        .folder = "/tmp/pg_api",
        .url = "http://localhost:3000/api/measurements"
    };
    pg_err_t err;
    err = pg_init();
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    pg_m_item_t* m1 = pg_new_measurement("api/test/pseudo_main/loop/ram", PG_MEASUREMENT_TYPE_RAM);
    CU_ASSERT(m1 != NULL);

    for (int i = 0; i < 10; i++) {
        // doing some stuff here
        err = pg_save_ram_usage(m1);
        CU_ASSERT_EQUAL(err, PG_NO_ERROR);
    }

    err = pg_stop_collecting(m1);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_collect(&c);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_stop();
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
}

void test_pseudo_main_progressive_ram_usage() {
    struct pg_config c = {
        .folder = "/tmp/pg_api",
        .url = "http://localhost:3000/api/measurements"
    };
    pg_err_t err;
    err = pg_init();
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    pg_m_item_t* m1 = pg_new_measurement("api/test/pseudo_main/progressive/ram", PG_MEASUREMENT_TYPE_RAM);
    CU_ASSERT(m1 != NULL);


    err = pg_save_ram_usage(m1);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    void *t1 = calloc(1*1024*1024, sizeof (int)); // 1 MiB
    
    err = pg_save_ram_usage(m1);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
    
    void *t2 = calloc(1*1024*1024, sizeof (int)); // 1 MiB
    
    err = pg_save_ram_usage(m1);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_stop_collecting(m1);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_collect(&c);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_stop();
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
 
    free(t1);
    free(t2);
}

void test_pseudo_main_loop_ram_usage_with_tag() {
    struct pg_config c = {
        .folder = "/tmp/pg_api",
        .url = "http://localhost:3000/api/measurements"
    };
    pg_err_t err;
    err = pg_init();
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    pg_m_item_t* m1 = pg_new_measurement("api/test/pseudo_main/loop/ram_usage_wtag", PG_MEASUREMENT_TYPE_RAM);
    CU_ASSERT(m1 != NULL);

    for (int i = 0; i < 10; i++) {
        // doing some stuff here
        err = pg_save_ram_usage_tag(m1, "test-tag");
        CU_ASSERT_EQUAL(err, PG_NO_ERROR);
    }

    err = pg_stop_collecting(m1);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_collect(&c);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_stop();
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("api-general", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    CU_add_test(pSuite, "test_pseudo_main", test_pseudo_main);
    CU_add_test(pSuite, "test_pseudo_main_init", test_pseudo_main_init);
    CU_add_test(pSuite, "test_pseudo_main_loop", test_pseudo_main_loop);
    CU_add_test(pSuite, "test_pseudo_main_loop_timestamp", test_pseudo_main_loop_timestamp);
    CU_add_test(pSuite, "test_pseudo_main_loop_timestamp_with_tag", test_pseudo_main_loop_timestamp_with_tag);
    CU_add_test(pSuite, "test_pseudo_main_loop_ram_usage", test_pseudo_main_loop_ram_usage);
    CU_add_test(pSuite, "test_pseudo_main_progressive_ram_usage", test_pseudo_main_progressive_ram_usage);
    CU_add_test(pSuite, "test_pseudo_main_loop_ram_usage_with_tag", test_pseudo_main_loop_ram_usage_with_tag);

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
