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

void test_pg_init() {
    pg_err_t result = pg_init();
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    /* destroy queue */
    size_t q_size = pg_clear_queue();
    CU_ASSERT_EQUAL(q_size, 0);
    result = pg_destroy_queue();
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
}

void test_pg_collect() {
    struct pg_config c = {
        .folder = "/tmp/pg",
        .repeat = 1
    };

    pg_err_t result = pg_collect(&c);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    // ---

    pg_m_item_t *m = pg_create_measurement_item();
    m->type = PG_MEASUREMENT_TYPE_HIT;
    m->path = strdup("pg_collect/test/hit");
    result = pg_publish_measurement(m);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    result = pg_destroy_measurement_item(m);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    size_t queue_size = pg_get_queue_size();
    CU_ASSERT_EQUAL(queue_size, 1);

    // ---

    result = pg_stop();
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
    
    /* destroy queue */
    size_t q_size = pg_clear_queue();
    CU_ASSERT_EQUAL(q_size, 0);
    result = pg_destroy_queue();
    CU_ASSERT_EQUAL(result, PG_ERR_QUEUE_NOT_READY);
}

void test_pg_harvest() {

    struct pg_config c = {
        .folder = "/tmp/pg",
        .repeat = 10
    };

    pg_err_t result = pg_collect(&c);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    // ---

    pg_m_item_t *m = pg_create_measurement_item();
    m->type = PG_MEASUREMENT_TYPE_HIT;
    m->path = strdup("pg_start/test/hit");
    result = pg_publish_measurement(m);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    result = pg_destroy_measurement_item(m);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    size_t queue_size = pg_get_queue_size();
    CU_ASSERT_EQUAL(queue_size, 1);

    // ---

   
    result = pg_stop();
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    /* destroy queue */
    size_t q_size = pg_clear_queue();
    CU_ASSERT_EQUAL(q_size, 0);
    result = pg_destroy_queue();
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
}

void test_pg_start() {

    struct pg_config c = {
        .folder = "/tmp/pg",
        .repeat = 10
    };

    pg_err_t result = pg_start(&c);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    // ---

    pg_m_item_t *m = pg_create_measurement_item();
    m->type = PG_MEASUREMENT_TYPE_HIT;
    m->path = strdup("pg_start/test/hit");
    result = pg_publish_measurement(m);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    result = pg_destroy_measurement_item(m);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    size_t queue_size = pg_get_queue_size();
    CU_ASSERT_EQUAL(queue_size, 1);

    // ---

   
    result = pg_stop();
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    /* destroy queue */
    size_t q_size = pg_clear_queue();
    CU_ASSERT_EQUAL(q_size, 0);
    result = pg_destroy_queue();
    CU_ASSERT_EQUAL(result, PG_ERR_QUEUE_NOT_READY);
}

void test_pg_stop() {
    struct pg_config c = {
        .folder = "/tmp/pg",
        .repeat = 10
    };

    pg_err_t result = pg_start(&c);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    // ---
    pg_m_item_t *m = pg_create_measurement_item();
    m->type = PG_MEASUREMENT_TYPE_HIT;
    m->path = strdup("pg_stop/test/hit");
    result = pg_publish_measurement(m);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    result = pg_destroy_measurement_item(m);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    size_t queue_size = pg_get_queue_size();
    CU_ASSERT_EQUAL(queue_size, 1);

    /* wait for thread to finish */
    result = pg_stop();
}

void test_pg_harvest_measurements(void) {
    pg_init_queue();

    pg_m_item_t *m = pg_create_measurement_item();
    m->type = PG_MEASUREMENT_TYPE_HIT;
    m->path = strdup("func1/test/hit");
    pg_err_t result = pg_publish_measurement(m);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    result = pg_destroy_measurement_item(m);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);

    size_t queue_size = pg_get_queue_size();
    CU_ASSERT_EQUAL(queue_size, 1);

    // ---

    pg_config_t *c = pg_create_config();
    c->folder = strdup("/tmp/");
    c->repeat = 10;

    pg_harvest_measurements(c);

    // ---

    /* destroy queue */
    result = pg_clear_queue();
    CU_ASSERT_EQUAL(result, 0);
    result = pg_destroy_queue();
    CU_ASSERT_EQUAL(result, 0);

}

void test_pg_register_js_functions() {
    duk_context *ctx = duk_create_heap_default();
    pg_err_t err = pg_register_js_functions(ctx);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
    duk_destroy_heap(ctx);
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
    CU_add_test(pSuite, "test_pg_init", test_pg_init);
    CU_add_test(pSuite, "test_pg_collect", test_pg_collect);
    CU_add_test(pSuite, "test_pg_harvest_measurements", test_pg_harvest_measurements);
    CU_add_test(pSuite, "test_pg_start", test_pg_start);
    CU_add_test(pSuite, "test_pg_stop", test_pg_stop);
    CU_add_test(pSuite, "test_pg_register_js_functions", test_pg_register_js_functions);


    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
