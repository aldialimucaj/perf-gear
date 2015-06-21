/** @brief Header file for Performance Gear 
 * 
 * @file   perf-gear.h
 * @author Aldi Alimucaj
 *
 * @date March 19, 2015, 10:33 PM
 * 
 * All API function to the perf-pear library.
 * 
 */

#ifndef PERF_GEAR_H
#define	PERF_GEAR_H

#include "pg-utils.h"

#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "queue.h"
#include "measurement2json.h"
#include "dispatcher.h"

#define PG_PUBLIC_API __attribute__((__visibility__("default")))

#define MILLISECOND  1000000L
#define HARVEST_WAIT_10MS 10L * MILLISECOND
#define HARVEST_WAIT_100MS 100L * MILLISECOND

#ifdef	__cplusplus
extern "C" {
#endif

    /** @brief Flag to stop harvesting measurements form the queue
     */
    extern bool pg_harvest;

    /** @brief Harvester thread
     */
    extern pthread_t harvester_th;
    
    /** @brief Initialize perf-gear internals
     * 
     * @return 
     */
    pg_err_t pg_init();
    
    /** @brief Starts the collecting mechanisms. 
     * 
     * Alias for pg_start if init was called beforehands.
     * 
     * @param config
     * @return 
     */
    pg_err_t pg_collect(pg_config_t *config);

    /** @brief Starts the writing and collecting mechanisms.
     * 
     * This way you initialize the queue and harvest all elements
     * imediatelly. If you want to collect the elements afterwards
     * call @see pg_init() and then @see pg_collect()
     * 
     * @param config
     * @return 
     */
    pg_err_t pg_start(pg_config_t *config);

    /** @brief Stop the measurement
     * 
     * @return 
     */
    pg_err_t pg_stop();


    /** @brief Collect finished measurements from the queue.
     * 
     * Published measurements land in the queue. From there
     * they can be collected through this function and sent
     * for dispatch.
     * 
     * @return finished emptying queue with error message
     */
    void* pg_harvest_measurements(void *cfg);



#ifdef	__cplusplus
}
#endif

#endif	/* PERF_GEAR_H */

