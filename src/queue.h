/** 
 * @file   queue.h
 * @author Aldi Alimucaj
 *
 * @date March 3, 2015, 10:33 AM
 * @brief Header file for Performance Gear dispatch queue
 * 
 * The queue acts as a dispatcher for finished measurement events.
 * Once an event is ready to be persisted it is sent to the queue for
 * dispatching. The queue is allocated in shared memory so that different
 * processes can access the content.
 * 
 */

#ifndef QUEUE_H
#define	QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PG_MEASUREMENT_TYPE_UNKNOWN -1
#define PG_MEASUREMENT_TYPE_HIT   0
#define PG_MEASUREMENT_TYPE_TIME  1


#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * @brief Shared memory queue for dispatching finished measurements.
     * 
     * The queue where all results from test measurements will be stored
     * and retrieved for storage and persistence.
     */
    struct pg_queue {
        struct pg_queue_item *head; /**< Head of the queue */
        struct pg_queue_item *tail; /**< Tail of the queue */
        long size;                  /**< Show the current number of elements */
    };

    /** @brief Representation of a queue item .
     * 
     * It contains a measurement structure and the next element if any.     
     */
    struct pg_queue_item {
        struct pg_measurement_item *measurement; /**< Measurement contect */
        struct pg_queue_item *next; /**< Next in line */
    };

    /** @brief Measurement result to be stored in a queue 
     */
    struct pg_measurement_item {
        char *path; /**< path describing the measurement eg. 'calc/math/fibonaci/hits' */
        char type; /**< Type of measurement HIT|TIME|MEMORY */
        long hitValue; /**< Value for hits */
        long timeSpentValue; /**< Value for time */
        struct pg_measurement_sequence *sequence; /**< a sequence of events */
    };

    /** @brief A sequence of measurement events
     *
     * The sequence measures a value over time and stores all the results
     * in a sequence array.
     */
    struct pg_measurement_sequence {
        long timestamp; /**< Time when it was measured */
        double value; /**< Value that was measured */
    };

    /** @brief The Queue */
    struct pg_queue *pg_queue;

    /** @brief Initializes the queue
     * 
     * Creates the queue if there is no queue already.
     * If there was one, it returns the current one without creating a new one.
     * 
     * @return pointer to the queue element.
     */
    struct pg_queue* pg_init_queue(void);

    /**
     * @brief Destroys the queue.
     * 
     * Releases the queue but before checks if the queue is empty.
     * A queue with elements cannot be intentionally destroyed because
     * information would go missing.
     * 
     * @return 0 = ok, error if the queue is not empty
     */
    int pg_destroy_queue(void);

    /** @brief Enqueue item into pg_queue 
     * 
     * This function creates a copy of the structure and leaves the old one
     * untouched.
     * 
     * @return 0 = ok
     */
    int pg_enqueue(struct pg_queue_item *item);


    /** 
     * @brief Pops the first element out of the queue
     * 
     * The element is still in the shared memory. No copy was made.
     * Make sure to clean up after finished using it.
     * 
     * @return Returns the first element from the queue. If no element exists or
     * the queue is not ready then it returns null. 
     */
    struct pg_queue_item* pg_dequeue(void);


    /** @brief Removes all elements from the queue
     * 
     * @return Returns the number of elements that were dequeued
     */
    int pg_clear_queue(void);


    /** @brief Returns the size of the queue
     * 
     * This means the number of elements in the queue.
     * 
     * @return number of elements
     */
    long pg_get_queue_size(void);

    /** @brief Creates a new queue element
     * 
     * Measurement and Next values are set to NULL.
     * 
     * @return Pointer to element
     */
    struct pg_queue_item* pg_create_queue_item(void);

    /** @brief Releases the item.
     * 
     * This also takes care of the sub elements.
     * 
     * @returns 0 = ok
     */
    int pg_destroy_queue_item(struct pg_queue_item *item);

    /** @brief Creates a new measurement element
     * 
     */
    struct pg_measurement_item* pg_create_measurement_item(void);

    /** @brief Releases the measurement item.
     * 
     * This also takes care of the sub elements.
     * 
     * @returns 0 = ok
     */
    int pg_destroy_measurement_item(struct pg_measurement_item *measurement_item);

    /** @brief Copy memory from source to destination
     * 
     * Measurement items are often copied around. This is a helper function for
     * copying the measurement form heap to shared memory.
     * 
     * @return 0 = ok.
     */
    int pg_copy_measurement_item(struct pg_measurement_item *src, struct pg_measurement_item *dst);

    /** @brief Creates a new measurement sequence
     * 
     * @return pointer to sequence
     */
    struct pg_measurement_sequence* pg_create_measurement_sequence(void);

    /** @brief Releases the item.
     * 
     * This also takes care of the sub elements.
     * 
     * @returns 0 = ok
     */
    int pg_destroy_measurement_sequence(struct pg_measurement_sequence *measurement_sequence);


#ifdef	__cplusplus
}
#endif

#endif	/* QUEUE_H */

