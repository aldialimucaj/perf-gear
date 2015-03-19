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

#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include "pg-utils.h"
#include "queue.h"
#include "measurement2json.h"
#include "dispatcher.h"

#define MILLISECOND  1000000L
#define HARVEST_WAIT_100MS 100L * MILLISECOND

#ifdef	__cplusplus
extern "C" {
#endif

    /** @brief Flag to stop harvesting measurements form the queue
     */
    static bool pg_harvest = false;
    
    

    /** @brief Collect finished measurements from the queue.
     * 
     * Published measurements land in the queue. From there
     * they can be collected through this function and sent
     * for dispatch.
     * 
     * @return finished emptying queue with error message
     */
    pg_err_t pg_harvest_measurements(pg_config_t config);



#ifdef	__cplusplus
}
#endif

#endif	/* PERF_GEAR_H */

