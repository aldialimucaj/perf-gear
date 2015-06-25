/** @brief Header file for Performance Gear dispatch queue
 * 
 * @file   queue.h
 * @author Aldi Alimucaj
 *
 * @date March 3, 2015, 10:33 AM
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
#include "pg-utils.h"


#ifdef	__cplusplus
extern "C" {
#endif

    /** @brief Shared memory queue for dispatching finished measurements.
     * 
     * The queue where all results from test measurements will be stored
     * and retrieved for storage and persistence.
     */
    struct pg_queue {
        struct pg_queue_item *head; /*!< Head of the queue */
        struct pg_queue_item *tail; /*!< Tail of the queue */
        size_t size; /**< Show the current number of elements */
    };

    /** @brief Representation of a queue item .
     * 
     * It contains a measurement structure and the next element if any.     
     */
    typedef struct pg_queue_item {
        struct pg_measurement_item *measurement; /*!< Measurement content */
        struct pg_queue_item *next; /*!< Next in line */
    } pg_q_item_t;

    /** @brief Measurement Types
     * 
     */
    typedef enum {
        PG_MEASUREMENT_TYPE_UNKNOWN = 0, /*!< is an undefined state and indicates an error. */
        PG_MEASUREMENT_TYPE_HIT = 1, /*!< counts the hits that this event has fired. */
        PG_MEASUREMENT_TYPE_TIME = 2 /*!< measures the time between event creation and destruction. */
    } pg_mtype_t;

    typedef enum {
        PG_MEASUREMENT_UNIT_UNKNOWN = 0, /*!< is an undefined state and indicates an error. */
        PG_MEASUREMENT_UNIT_HIT, /*!< counts the hits. scalar type */
        PG_MEASUREMENT_UNIT_NS, /*!< nanoseconds. */
        PG_MEASUREMENT_UNIT_MS, /*!< milliseconds. */
        PG_MEASUREMENT_UNIT_SC, /*!< seconds. */
        PG_MEASUREMENT_UNIT_MB, /*!< Megabyte. */
        PG_MEASUREMENT_UNIT_KB, /*!< Kilobyte. */
        PG_MEASUREMENT_UNIT_BT /*!< Byte. */
    } pg_munit_t;

    typedef enum {
        PG_PARAM_TYPE_UNKNOWN = 0, /*!< is an undefined state and indicates an error. */
        PG_PARAM_TYPE_STR, /*!< string. */
        PG_PARAM_TYPE_INT, /*!< integer. */
        PG_PARAM_TYPE_DBL, /*!< double. */
        PG_PARAM_TYPE_OBJ, /*!< object that contains sub parameters. */
    } pg_param_type_t;
    
    /** @brief Measurement parameter in order to add key value elements
     */
    typedef struct pg_measurement_param {
        char *key; /*!< REQUIRED: key */
        size_t intValue; /*!< int value */
        double doubleValue; /*!< double value */
        char *strValue; /*!< str value */
        struct pg_measurement_param *objValue; /**< object value */
        pg_param_type_t type; /**< REQUIRED: type to be interpreted when marshalling */
        struct pg_measurement_param *next; /**< next parameter */
    } pg_m_param_t;
    

    /** @brief Measurement result to be stored in a queue 
     */
    typedef struct pg_measurement_item {
        char *path; /*!< path describing the measurement eg. 'calc/math/fibonaci/hits' */
        pg_mtype_t type; /*!< Type of measurement HIT|TIME|MEMORY */
        size_t hitValue; /*!< Value for hits */
        pg_munit_t unit; /*!< Unit to interpret the data */
        struct pg_measurement_sequence *sequence; /**< a sequence of events */
        pg_m_param_t *param; /**< key value parameters */
    } pg_m_item_t;

    /** @brief A sequence of measurement events
     *
     * The sequence measures a value over time and stores all the results
     * in a sequence array.
     */
    typedef struct pg_measurement_sequence {
        size_t timestamp; /*!< Time when it was measured */
        double value; /*!< Value that was measured */
        struct pg_measurement_sequence* next; /*!< Next sequence */
    } pg_mseq_t;

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

    /** @brief Destroys the queue.
     * 
     * Releases the queue but before checks if the queue is empty.
     * A queue with elements cannot be intentionally destroyed because
     * information would go missing.
     * 
     * @return 0 = ok, error if the queue is not empty
     */
    pg_err_t pg_destroy_queue(void);

    /** @brief Enqueue item into pg_queue 
     * 
     * This function creates a copy of the structure and leaves the old one
     * untouched.
     * 
     * @return 0 = ok
     */
    pg_err_t pg_enqueue(pg_q_item_t *item);


    /** @brief Pops the first element out of the queue
     * 
     * The element is still in the shared memory. No copy was made.
     * Make sure to clean up after finished using it.
     * 
     * @return Returns the first element from the queue. If no element exists or
     * the queue is not ready then it returns null. 
     */
    pg_q_item_t* pg_dequeue(void);


    /** @brief Removes all elements from the queue
     * 
     * @return Returns the number of elements that were dequeued
     */
    size_t pg_clear_queue(void);


    /** @brief Returns the size of the queue
     * 
     * This means the number of elements in the queue.
     * 
     * @return number of elements
     */
    size_t pg_get_queue_size(void);

    /** @brief Creates a new queue element
     * 
     * Measurement and Next values are set to NULL.
     * 
     * @return Pointer to element
     */
    pg_q_item_t* pg_create_queue_item(void);

    /** @brief Releases the item.
     * 
     * This also takes care of the sub elements.
     * 
     * @param item
     * 
     * @returns 0 = ok
     */
    pg_err_t pg_destroy_queue_item(pg_q_item_t *item);

    /** @brief Creates a new measurement element
     * 
     */
    pg_m_item_t* pg_create_measurement_item(void);

    /** @brief Releases the measurement item.
     * 
     * This also takes care of the sub elements.
     * 
     * @param item to be destroyed
     * 
     * @returns 0 = ok
     */
    pg_err_t pg_destroy_measurement_item(pg_m_item_t *item);

    /** @brief Copy memory from source to destination
     * 
     * Measurement items are often copied around. This is a helper function for
     * copying the measurement form heap to shared memory.
     * 
     * @param src source item to copy from
     * @param dst destination to copy to. pre allocated.
     * 
     * @return 0 = ok.
     */
    pg_err_t pg_copy_measurement_item(pg_m_item_t *src, pg_m_item_t *dst);

    /** @brief Creates a new measurement sequence
     * 
     * @return pointer to sequence
     */
    pg_mseq_t* pg_create_measurement_sequence(void);

    /** @brief Releases the item.
     * 
     * This also takes care of the sub elements.
     * 
     * @param item sequence to destroy
     * 
     * @returns 0 = ok
     */
    pg_err_t pg_destroy_measurement_sequence(pg_mseq_t *item);


    /** @brief Adds new sequence item to the measurement
     * 
     * @param measurement
     * @param seq
     * @return 
     */
    pg_err_t pg_add_measurement_sequence(pg_m_item_t *measurement, pg_mseq_t *seq);

    /** @brief Copy measurement sequences
     * 
     * Copies the linked list of measurement sequences
     * 
     * @param src
     * @param dst
     * @return 
     */
    pg_err_t pg_copy_measurement_sequences(pg_m_item_t *src, pg_m_item_t *dst);

    /** @brief Count measurement sequences in this measurement item
     * 
     * @param measurement
     * @return Sequences counted
     */
    size_t pg_count_measurement_sequences(pg_m_item_t *measurement);

    /** @brief Clears all measurements sequences.
     * 
     * @param measurement
     * @return The number of sequences destroyed
     */
    size_t pg_clear_all_measurement_sequences(pg_m_item_t *measurement);
    
    /** @brief Create new parameter
     * 
     * @param key
     * @param type
     * @return pg_m_param_t
     */
    pg_m_param_t* pg_create_measurement_param(const char *key, pg_param_type_t type);
    
    /** @brief Destroy parameter
     * 
     * @param param
     * @return 
     */
    pg_err_t pg_destroy_measurement_param(pg_m_param_t *param);
    
    /** @brief Copy parameters recursively from source to destination
     * 
     * @param src
     * @param dst
     */
    pg_err_t pg_param_copy_helper(pg_m_param_t *src, pg_m_param_t *dst);
    
    /** @brief Copy measurement sequences
     * 
     * Copies the linked list of measurement sequences
     * 
     * @param src
     * @param dst
     * @return 
     */
    pg_err_t pg_copy_measurement_params(pg_m_item_t *src, pg_m_item_t *dst);

    /** @brief Add parameter to the measurement that will be persisted into JSON
     * 
     * Adding string parameters
     * 
     * @param measurement
     * @param key
     * @param val
     * @return 
     */
    pg_err_t pg_msrt_add_param_str(pg_m_item_t *measurement, const char *key, const char *val);


#ifdef	__cplusplus
}
#endif

#endif	/* QUEUE_H */

