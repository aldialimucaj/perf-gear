/*
 * File:   queue-test.c
 * Author: Aldi Alimucaj
 *
 * Created on Mar 4, 2015, 8:09:40 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "../src/queue.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_pg_init_queue() {
    struct pg_queue* result = pg_init_queue();
    CU_ASSERT_PTR_NOT_NULL(result);
    pg_destroy_queue();

    /* create twice */
    struct pg_queue* result1 = pg_init_queue();
    CU_ASSERT_PTR_NOT_NULL(result1);
    struct pg_queue* result2 = pg_init_queue();
    CU_ASSERT_PTR_NOT_NULL(result2);
    CU_ASSERT_EQUAL(result1, result2);
    pg_destroy_queue();

}

void test_pg_destroy_queue() {
    pg_init_queue();
    int result = pg_destroy_queue();
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
    CU_ASSERT_PTR_NULL(pg_queue);

    /* destroy twice */
    pg_init_queue();
    int result2 = pg_destroy_queue();
    CU_ASSERT_EQUAL(result2, PG_NO_ERROR);
    CU_ASSERT_PTR_NULL(pg_queue);
    result2 = pg_destroy_queue();
    CU_ASSERT_EQUAL(result2, PG_ERR_QUEUE_NOT_READY);
    CU_ASSERT_PTR_NULL(pg_queue);

    /* try to destroy with element */
    pg_init_queue();
    struct pg_queue_item* new_item = pg_create_queue_item();
    CU_ASSERT_PTR_NOT_NULL(new_item);
    int result3 = pg_enqueue(new_item);
    CU_ASSERT_EQUAL(result3, PG_NO_ERROR);
    /* destroy item after enqueue */
    result3 = pg_destroy_queue_item(new_item);
    CU_ASSERT_EQUAL(result3, PG_NO_ERROR);
    result3 = pg_destroy_queue();
    CU_ASSERT_EQUAL(result3, PG_ERR_QUEUE_NOT_EMPTY);
    CU_ASSERT_PTR_NOT_NULL(pg_queue);
    /* clear queue */
    result3 = pg_clear_queue();
    CU_ASSERT_EQUAL(result3, 1);
    /* try again */
    result3 = pg_destroy_queue();
    CU_ASSERT_EQUAL(result3, PG_NO_ERROR);
    CU_ASSERT_PTR_NULL(pg_queue);
}

void test_pg_enqueue() {
    pg_init_queue();
    /* queue is ready */

    struct pg_queue_item* new_item = pg_create_queue_item();
    CU_ASSERT_PTR_NOT_NULL(new_item);
    int result = pg_enqueue(new_item);
    CU_ASSERT_EQUAL(result, 0);
    long queue_size = pg_get_queue_size();
    CU_ASSERT_EQUAL(queue_size, 1);

    /* enqueue makes a copy of the item */
    /* the old one needs to be freed if not needed */
    pg_destroy_queue_item(new_item);

    /* destroy queue */
    result = pg_clear_queue();
    CU_ASSERT_EQUAL(result, 1);
    result = pg_destroy_queue();
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_PTR_NULL(pg_queue);
}

void test_pg_enqueue_many() {
    pg_init_queue();
    /* queue is ready */
    int queue_elements = 100;
    int index = 0;
    while (index++ < queue_elements) {
        struct pg_queue_item* new_item = pg_create_queue_item();
        CU_ASSERT_PTR_NOT_NULL(new_item);
        int result = pg_enqueue(new_item);
        CU_ASSERT_EQUAL(result, 0);
        long queue_size = pg_get_queue_size();
        CU_ASSERT_EQUAL(queue_size, index);

        /* enqueue makes a copy of the item */
        /* the old one needs to be freed if not needed */
        pg_destroy_queue_item(new_item);
    }

    /* destroy queue */
    int result = pg_clear_queue();
    CU_ASSERT_EQUAL(result, 100);
    result = pg_destroy_queue();
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_PTR_NULL(pg_queue);
}

void test_pg_enqueue_with_content() {
    pg_init_queue();
    /* queue is ready */

    struct pg_queue_item* new_item = pg_create_queue_item();
    CU_ASSERT_PTR_NOT_NULL(new_item);
    new_item->measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(new_item->measurement);
    char *txt = "test/one/item";
    new_item->measurement->path = malloc(sizeof (char)*strlen(txt) + 1);
    strcpy(new_item->measurement->path, txt);
    new_item->measurement->type = PG_MEASUREMENT_TYPE_HIT;
    new_item->measurement->hitValue = 10;


    /* ENQUEUE */
    int result = pg_enqueue(new_item);
    CU_ASSERT_EQUAL(result, 0);
    long queue_size = pg_get_queue_size();
    CU_ASSERT_EQUAL(queue_size, 1);

    /* enqueue makes a copy of the item */
    /* the old one needs to be freed if not needed */
    pg_destroy_queue_item(new_item);

    /* DEQUEUE AND CHECK */
    struct pg_queue_item* old_item = pg_dequeue();
    CU_ASSERT_PTR_NOT_NULL(old_item);
    CU_ASSERT_PTR_NOT_NULL(old_item->measurement);
    CU_ASSERT_STRING_EQUAL(old_item->measurement->path, "test/one/item");
    CU_ASSERT_EQUAL(old_item->measurement->type, PG_MEASUREMENT_TYPE_HIT);
    CU_ASSERT_EQUAL(old_item->measurement->hitValue, 10);
    pg_destroy_queue_item(old_item);

    /* destroy queue */
    result = pg_clear_queue();
    CU_ASSERT_EQUAL(result, 0);
    result = pg_destroy_queue();
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_PTR_NULL(pg_queue);
}

void test_pg_dequeue() {
    pg_init_queue();
    /* queue is ready */

    pg_m_item_t *measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);

    pg_q_item_t *q_item = pg_create_queue_item();
    CU_ASSERT_PTR_NOT_NULL(q_item);

    q_item->measurement = measurement;
    int result = pg_enqueue(q_item);
    CU_ASSERT_EQUAL(result, 0);

    /* DEQUEUE AND CHECK */
    struct pg_queue_item* old_item = pg_dequeue();
    CU_ASSERT_PTR_NOT_NULL(old_item);
    result = pg_destroy_queue_item(q_item);
    CU_ASSERT_EQUAL(result, 0);
    result = pg_destroy_queue_item(old_item);
    CU_ASSERT_EQUAL(result, 0);

    /* destroy queue */
    result = pg_clear_queue();
    CU_ASSERT_EQUAL(result, 0);
    result = pg_destroy_queue();
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_PTR_NULL(pg_queue);
}

void test_pg_clear_queue() {
    pg_init_queue();
    /* queue is ready */

    const int REPEAT = 1000;
    int index = 0;
    while (index++ < REPEAT) {
        pg_q_item_t *q_item = pg_create_queue_item();
        CU_ASSERT_PTR_NOT_NULL(q_item);

        pg_m_item_t *measurement = pg_create_measurement_item();
        CU_ASSERT_PTR_NOT_NULL(measurement);
        q_item->measurement = measurement;

        int res = pg_enqueue(q_item);
        CU_ASSERT_EQUAL(res, 0);
        res = pg_destroy_queue_item(q_item);
        CU_ASSERT_EQUAL(res, 0);
    }


    /* destroy queue */
    int result = pg_clear_queue();
    CU_ASSERT_EQUAL(result, REPEAT);
    result = pg_destroy_queue();
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_PTR_NULL(pg_queue);
}

void test_pg_get_queue_size() {
    pg_init_queue();
    /* queue is ready */

    const int REPEAT = 1234;
    int index = 0;
    while (index++ < REPEAT) {
        pg_q_item_t *q_item = pg_create_queue_item();
        CU_ASSERT_PTR_NOT_NULL(q_item);

        pg_m_item_t *measurement = pg_create_measurement_item();
        CU_ASSERT_PTR_NOT_NULL(measurement);
        q_item->measurement = measurement;

        int res = pg_enqueue(q_item);
        CU_ASSERT_EQUAL(res, 0);
        res = pg_destroy_queue_item(q_item);
        CU_ASSERT_EQUAL(res, 0);
    }

    long size = pg_get_queue_size();
    CU_ASSERT_EQUAL(size, REPEAT);

    /* destroy queue */
    int result = pg_clear_queue();
    CU_ASSERT_EQUAL(result, REPEAT);
    result = pg_destroy_queue();
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_PTR_NULL(pg_queue);
}

void test_pg_create_queue_item() {
    pg_q_item_t *q_item = pg_create_queue_item();
    CU_ASSERT_PTR_NOT_NULL(q_item);
    int result = pg_destroy_queue_item(q_item);
    CU_ASSERT_EQUAL(result, PG_NO_ERROR);
}

void test_pg_destroy_queue_item() {
    pg_q_item_t *q_item = pg_create_queue_item();
    CU_ASSERT_PTR_NOT_NULL(q_item);

    pg_m_item_t *measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);
    q_item->measurement = measurement;
    measurement->path = strdup("test/func/one");

    pg_mseq_t *seq = pg_create_measurement_sequence();
    int result = pg_add_measurement_sequence(measurement, seq);
    CU_ASSERT_EQUAL(result, 0);

    result = pg_destroy_queue_item(q_item);
}

void test_pg_create_measurement_item() {
    pg_m_item_t *measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);
    measurement->path = strdup("test/func/one");

    pg_mseq_t *seq = pg_create_measurement_sequence();
    int result = pg_add_measurement_sequence(measurement, seq);
    CU_ASSERT_EQUAL(result, 0);

    result = pg_destroy_measurement_item(measurement);
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_destroy_measurement_item() {
    int result = pg_destroy_measurement_item(NULL);
    CU_ASSERT_EQUAL(result, PG_ERR_NO_MEASUREMENT);

    pg_m_item_t *measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);
    measurement->path = strdup("test/func/one");

    pg_mseq_t *seq = pg_create_measurement_sequence();
    result = pg_add_measurement_sequence(measurement, seq);
    CU_ASSERT_EQUAL(result, 0);

    result = pg_destroy_measurement_item(measurement);
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_copy_measurement_item() {
    int result = pg_copy_measurement_item(NULL, NULL);
    CU_ASSERT_EQUAL(result, PG_ERR_NO_SOURCE);
    pg_m_item_t *measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);
    measurement->path = strdup("test/func/one");

    pg_mseq_t *seq = pg_create_measurement_sequence();
    result = pg_add_measurement_sequence(measurement, seq);
    CU_ASSERT_EQUAL(result, 0);

    result = pg_copy_measurement_item(measurement, NULL);
    CU_ASSERT_EQUAL(result, PG_ERR_NO_DESTINATION);

    pg_m_item_t *dst_m = pg_create_measurement_item();
    result = pg_copy_measurement_item(measurement, dst_m);


    CU_ASSERT_EQUAL(result, 0);

    result = pg_destroy_measurement_item(measurement);
    CU_ASSERT_EQUAL(result, 0);
    result = pg_destroy_measurement_item(dst_m);
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_create_measurement_sequence() {
    pg_mseq_t *seq = pg_create_measurement_sequence();
    CU_ASSERT_PTR_NOT_NULL(seq);
    int result = pg_destroy_measurement_sequence(seq);
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_destroy_measurement_sequence() {
    pg_mseq_t *seq = pg_create_measurement_sequence();
    CU_ASSERT_PTR_NOT_NULL(seq);
    int result = pg_destroy_measurement_sequence(seq);
    CU_ASSERT_EQUAL(result, 0);
    result = pg_destroy_measurement_sequence(NULL);
    CU_ASSERT_EQUAL(result, PG_ERR_NO_MEASUREMENT_SEQ);
}

void test_pg_add_measurement_sequence() {
    int result = pg_copy_measurement_item(NULL, NULL);
    CU_ASSERT_EQUAL(result, PG_ERR_NO_SOURCE);
    pg_m_item_t *measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);

    const int REPEAT = 1000;
    int index = 0;
    while (index++ < REPEAT) {
        pg_mseq_t *seq = pg_create_measurement_sequence();
        CU_ASSERT_PTR_NOT_NULL(seq);
        result = pg_add_measurement_sequence(measurement, seq);
        CU_ASSERT_EQUAL(result, 0);
    }

    long size = pg_count_measurement_sequences(measurement);
    CU_ASSERT_EQUAL(size, REPEAT);

    result = pg_destroy_measurement_item(measurement);
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_copy_measurement_sequences() {
    pg_m_item_t *measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);

    pg_m_item_t *dst_m = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(dst_m);

    int result = 0;

    const int REPEAT = 1000;
    int index = 0;
    while (index++ < REPEAT) {
        pg_mseq_t *seq = pg_create_measurement_sequence();
        CU_ASSERT_PTR_NOT_NULL(seq);
        result = pg_add_measurement_sequence(measurement, seq);
        CU_ASSERT_EQUAL(result, 0);
    }

    long size = pg_count_measurement_sequences(measurement);
    CU_ASSERT_EQUAL(size, REPEAT);

    result = pg_copy_measurement_sequences(measurement, dst_m);
    CU_ASSERT_EQUAL(result, 0);
    size = pg_count_measurement_sequences(measurement);
    CU_ASSERT_EQUAL(size, REPEAT);

    result = pg_destroy_measurement_item(measurement);
    CU_ASSERT_EQUAL(result, 0);
    result = pg_destroy_measurement_item(dst_m);
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_count_measurement_sequences() {
    int result = pg_copy_measurement_item(NULL, NULL);
    CU_ASSERT_EQUAL(result, PG_ERR_NO_SOURCE);
    pg_m_item_t *measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);

    const int REPEAT = 1854;
    int index = 0;
    while (index++ < REPEAT) {
        pg_mseq_t *seq = pg_create_measurement_sequence();
        CU_ASSERT_PTR_NOT_NULL(seq);
        result = pg_add_measurement_sequence(measurement, seq);
        CU_ASSERT_EQUAL(result, 0);
    }

    long size = pg_count_measurement_sequences(measurement);
    CU_ASSERT_EQUAL(size, REPEAT);

    result = pg_destroy_measurement_item(measurement);
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_clear_all_measurement_sequences() {
    pg_m_item_t *measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);

    const int REPEAT = 1854;
    int index = 0;
    int result = 0;
    while (index++ < REPEAT) {
        pg_mseq_t *seq = pg_create_measurement_sequence();
        CU_ASSERT_PTR_NOT_NULL(seq);
        result = pg_add_measurement_sequence(measurement, seq);
        CU_ASSERT_EQUAL(result, 0);
    }

    long size = pg_count_measurement_sequences(measurement);
    CU_ASSERT_EQUAL(size, REPEAT);

    long size_cleared = pg_clear_all_measurement_sequences(measurement);
    CU_ASSERT_EQUAL(size_cleared, REPEAT);

    size = pg_count_measurement_sequences(measurement);
    CU_ASSERT_EQUAL(size, 0);

    result = pg_destroy_measurement_item(measurement);
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_create_measurement_param() {
    pg_m_param_t *param = pg_create_measurement_param("test", PG_PARAM_TYPE_STR);
    CU_ASSERT_FATAL(param != NULL);
    CU_ASSERT_EQUAL(param->type, PG_PARAM_TYPE_STR);
    CU_ASSERT(param->key != NULL);
    CU_ASSERT(param->strValue == NULL);
    CU_ASSERT(param->intValue == 0);
    CU_ASSERT(param->doubleValue == 0.0);

    pg_destroy_measurement_param(param);
}

void test_pg_destroy_measurement_param() {
    pg_m_param_t *param = pg_create_measurement_param("test", PG_PARAM_TYPE_STR);
    CU_ASSERT_FATAL(param != NULL);
    param->strValue = strdup("test-value");
    pg_err_t err = pg_destroy_measurement_param(param);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    pg_m_param_t *param1 = pg_create_measurement_param("test", PG_PARAM_TYPE_OBJ);
    CU_ASSERT_FATAL(param1 != NULL);
    param1->objValue = pg_create_measurement_param("sub-test", PG_PARAM_TYPE_STR);
    err = pg_destroy_measurement_param(param1);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
}

void test_pg_msrt_add_param_str() {
    pg_m_item_t *measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL_FATAL(measurement);

    pg_err_t err = pg_msrt_add_param_str(measurement, "key", "value");
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_msrt_add_param_str(measurement, "key2", "value2");
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
    
    err = pg_msrt_add_param_str(measurement, "key3", "value3");
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    pg_destroy_measurement_item(measurement);
}

void test_pg_param_copy_helper() {
    pg_m_param_t *src = pg_create_measurement_param("key1", PG_PARAM_TYPE_STR);
    src->strValue = PG_STRDUP("value1");
    pg_m_param_t *src2 = pg_create_measurement_param("key2", PG_PARAM_TYPE_INT);
    src2->intValue = 99;
    src->next = src2;

    pg_m_param_t *src3 = pg_create_measurement_param("key3", PG_PARAM_TYPE_OBJ);
    pg_m_param_t *src31 = pg_create_measurement_param("key31", PG_PARAM_TYPE_STR);
    src31->strValue = PG_STRDUP("value31");
    src3->objValue = src31;
    src2->next = src3;


    pg_m_param_t *dst = pg_create_measurement_param("key1", PG_PARAM_TYPE_STR);
    pg_err_t err = pg_param_copy_helper(src, dst);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
    CU_ASSERT_STRING_EQUAL(src->strValue, dst->strValue);
    CU_ASSERT_EQUAL(src->next->intValue, dst->next->intValue);
    CU_ASSERT_STRING_EQUAL(src->next->next->key, dst->next->next->key);
    CU_ASSERT_STRING_EQUAL(src->next->next->objValue->strValue, dst->next->next->objValue->strValue);

    pg_m_param_t *unknown = pg_create_measurement_param("unknown1", PG_PARAM_TYPE_UNKNOWN);
    pg_m_param_t *u_dst = pg_create_measurement_param("unknown1", PG_PARAM_TYPE_UNKNOWN);
    err = pg_param_copy_helper(unknown, u_dst);
    CU_ASSERT_EQUAL(err, PG_ERR_BAD_ARG);

    pg_destroy_measurement_param(src);
    pg_destroy_measurement_param(src2);
    pg_destroy_measurement_param(src3);
    // no need to destroy src31 sub objects are taken care of
    pg_destroy_measurement_param(dst->next->next);
    pg_destroy_measurement_param(dst->next);
    pg_destroy_measurement_param(dst);

    pg_destroy_measurement_param(unknown);
    pg_destroy_measurement_param(u_dst);


}

void test_pg_copy_measurement_params() {
    pg_m_item_t *m1 = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL_FATAL(m1);
    pg_m_item_t *m2 = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL_FATAL(m2);

    pg_err_t err = pg_msrt_add_param_str(m1, "key1", "value1");
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);

    err = pg_copy_measurement_params(m1, m2);
    CU_ASSERT_EQUAL(err, PG_NO_ERROR);
    CU_ASSERT_STRING_EQUAL(m1->param->key, m2->param->key);


    pg_destroy_measurement_item(m1);
    pg_destroy_measurement_item(m2);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("queue_test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    CU_add_test(pSuite, "test_pg_init_queue", test_pg_init_queue);
    CU_add_test(pSuite, "test_pg_enqueue", test_pg_enqueue);
    CU_add_test(pSuite, "test_pg_enqueue_many", test_pg_enqueue_many);
    CU_add_test(pSuite, "test_pg_enqueue_with_content", test_pg_enqueue_with_content);
    CU_add_test(pSuite, "test_pg_dequeue", test_pg_dequeue);
    CU_add_test(pSuite, "test_pg_clear_queue", test_pg_clear_queue);
    CU_add_test(pSuite, "test_pg_get_queue_size", test_pg_get_queue_size);
    CU_add_test(pSuite, "test_pg_create_queue_item", test_pg_create_queue_item);
    CU_add_test(pSuite, "test_pg_destroy_queue_item", test_pg_destroy_queue_item);
    CU_add_test(pSuite, "test_pg_destroy_queue", test_pg_destroy_queue);
    CU_add_test(pSuite, "test_pg_create_measurement_item", test_pg_create_measurement_item);
    CU_add_test(pSuite, "test_pg_destroy_measurement_item", test_pg_destroy_measurement_item);
    CU_add_test(pSuite, "test_pg_copy_measurement_item", test_pg_copy_measurement_item);
    CU_add_test(pSuite, "test_pg_create_measurement_sequence", test_pg_create_measurement_sequence);
    CU_add_test(pSuite, "test_pg_destroy_measurement_sequence", test_pg_destroy_measurement_sequence);
    CU_add_test(pSuite, "test_pg_add_measurement_sequence", test_pg_add_measurement_sequence);
    CU_add_test(pSuite, "test_pg_copy_measurement_sequences", test_pg_copy_measurement_sequences);
    CU_add_test(pSuite, "test_pg_count_measurement_sequences", test_pg_count_measurement_sequences);
    CU_add_test(pSuite, "test_pg_clear_all_measurement_sequences", test_pg_clear_all_measurement_sequences);
    CU_add_test(pSuite, "test_pg_create_measurement_param", test_pg_create_measurement_param);
    CU_add_test(pSuite, "test_pg_destroy_measurement_param", test_pg_destroy_measurement_param);
    CU_add_test(pSuite, "test_pg_param_copy_helper", test_pg_param_copy_helper);
    CU_add_test(pSuite, "test_pg_copy_measurement_params", test_pg_copy_measurement_params);
    CU_add_test(pSuite, "test_pg_msrt_add_param_str", test_pg_msrt_add_param_str);


    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
