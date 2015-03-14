/*
 * File:   queue_test.c
 * Author: garmin
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
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_PTR_NULL(pg_queue);

    /* destroy twice */
    pg_init_queue();
    int result2 = pg_destroy_queue();
    CU_ASSERT_EQUAL(result2, 0);
    CU_ASSERT_PTR_NULL(pg_queue);
    int result3 = pg_destroy_queue();
    CU_ASSERT_EQUAL(result3, 1);
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

    pg_m_item_t measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);

    pg_q_item_t q_item = pg_create_queue_item();
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
        pg_q_item_t q_item = pg_create_queue_item();
        CU_ASSERT_PTR_NOT_NULL(q_item);

        pg_m_item_t measurement = pg_create_measurement_item();
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
        pg_q_item_t q_item = pg_create_queue_item();
        CU_ASSERT_PTR_NOT_NULL(q_item);

        pg_m_item_t measurement = pg_create_measurement_item();
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
    pg_q_item_t q_item = pg_create_queue_item();
    CU_ASSERT_PTR_NOT_NULL(q_item);
    int result = pg_destroy_queue_item(q_item);
}

void test_pg_destroy_queue_item() {
    pg_q_item_t q_item = pg_create_queue_item();
    CU_ASSERT_PTR_NOT_NULL(q_item);

    pg_m_item_t measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);
    q_item->measurement = measurement;
    measurement->path = strdup("test/func/one");

    pg_mseq_t seq = pg_create_measurement_sequence();
    int result = pg_add_measurement_sequence(measurement, seq);
    CU_ASSERT_EQUAL(result, 0);

    result = pg_destroy_queue_item(q_item);
}

void test_pg_create_measurement_item() {
    pg_m_item_t measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);
    measurement->path = strdup("test/func/one");

    pg_mseq_t seq = pg_create_measurement_sequence();
    int result = pg_add_measurement_sequence(measurement, seq);
    CU_ASSERT_EQUAL(result, 0);

    result = pg_destroy_measurement_item(measurement);
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_destroy_measurement_item() {
    int result = pg_destroy_measurement_item(NULL);
    CU_ASSERT_EQUAL(result, 1);

    pg_m_item_t measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);
    measurement->path = strdup("test/func/one");

    pg_mseq_t seq = pg_create_measurement_sequence();
    result = pg_add_measurement_sequence(measurement, seq);
    CU_ASSERT_EQUAL(result, 0);

    result = pg_destroy_measurement_item(measurement);
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_copy_measurement_item() {
    int result = pg_copy_measurement_item(NULL, NULL);
    CU_ASSERT_EQUAL(result, 1);
    pg_m_item_t measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);
    measurement->path = strdup("test/func/one");

    pg_mseq_t seq = pg_create_measurement_sequence();
    result = pg_add_measurement_sequence(measurement, seq);
    CU_ASSERT_EQUAL(result, 0);

    result = pg_copy_measurement_item(measurement, NULL);
    CU_ASSERT_EQUAL(result, 2);

    pg_m_item_t dst_m = pg_create_measurement_item();
    result = pg_copy_measurement_item(measurement, dst_m);


    CU_ASSERT_EQUAL(result, 0);

    result = pg_destroy_measurement_item(measurement);
    CU_ASSERT_EQUAL(result, 0);
    result = pg_destroy_measurement_item(dst_m);
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_create_measurement_sequence() {
    pg_mseq_t seq = pg_create_measurement_sequence();
    CU_ASSERT_PTR_NOT_NULL(seq);
    int result = pg_destroy_measurement_sequence(seq);
    CU_ASSERT_EQUAL(result, 0);
}

void test_pg_destroy_measurement_sequence() {
    pg_mseq_t seq = pg_create_measurement_sequence();
    CU_ASSERT_PTR_NOT_NULL(seq);
    int result = pg_destroy_measurement_sequence(seq);
    CU_ASSERT_EQUAL(result, 0);
    result = pg_destroy_measurement_sequence(NULL);
    CU_ASSERT_EQUAL(result, 1);
}

void test_pg_add_measurement_sequence() {
    int result = pg_copy_measurement_item(NULL, NULL);
    CU_ASSERT_EQUAL(result, 1);
    pg_m_item_t measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);

    const int REPEAT = 1000;
    int index = 0;
    while (index++ < REPEAT) {
        pg_mseq_t seq = pg_create_measurement_sequence();
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
    pg_m_item_t measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);

    pg_m_item_t dst_m = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(dst_m);

    int result = 0;

    const int REPEAT = 1000;
    int index = 0;
    while (index++ < REPEAT) {
        pg_mseq_t seq = pg_create_measurement_sequence();
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
    CU_ASSERT_EQUAL(result, 1);
    pg_m_item_t measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);

    const int REPEAT = 1854;
    int index = 0;
    while (index++ < REPEAT) {
        pg_mseq_t seq = pg_create_measurement_sequence();
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
    int result = pg_copy_measurement_item(NULL, NULL);
    CU_ASSERT_EQUAL(result, 1);
    pg_m_item_t measurement = pg_create_measurement_item();
    CU_ASSERT_PTR_NOT_NULL(measurement);

    const int REPEAT = 1854;
    int index = 0;
    while (index++ < REPEAT) {
        pg_mseq_t seq = pg_create_measurement_sequence();
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


    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
