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

#include "duktape.h"

#include "queue.h"
#include "measurement2json.h"
#include "dispatcher.h"
#include "collector.h"
#include "dukbridge.h"

#define PG_PUBLIC_API __attribute__((__visibility__("default")))

#define MILLISECOND  1000000L
#define HARVEST_WAIT_10MS 10L * MILLISECOND
#define HARVEST_WAIT_100MS 100L * MILLISECOND

#define PG_LOCALHOST_URL "http://localhost:3000/api/measurements"

#ifdef	__cplusplus
extern "C" {
#endif

    /** @brief Flag to stop harvesting measurements form the queue
     */
    extern volatile bool pg_harvest;

    /** @brief Harvester thread
     */
    extern pthread_t harvester_th;
    
    /** @brief context for duktape
     */
    extern duk_context *duk_ctx;
    
    /** @brief Initialize perf-gear internals
     * 
     * @return 
     */
    PG_PUBLIC_API pg_err_t pg_init();
    
    /** @brief Starts the collecting mechanisms. 
     * 
     * Alias for pg_start if init was called beforehands.
     * 
     * @param config
     * @return 
     */
    PG_PUBLIC_API pg_err_t pg_collect(pg_config_t *config);

    /** @brief Starts the writing and collecting mechanisms.
     * 
     * This way you initialize the queue and harvest all elements
     * immediately. If you want to collect the elements afterwards
     * call @see pg_init() and then @see pg_collect()
     * 
     * @param config
     * @return 
     */
    PG_PUBLIC_API pg_err_t pg_start(pg_config_t *config);

    /** @brief Stop the measurement
     * 
     * @return 
     */
    PG_PUBLIC_API pg_err_t pg_stop();


    /** @brief Collect finished measurements from the queue.
     * 
     * Published measurements land in the queue. From there
     * they can be collected through this function and sent
     * for dispatch.
     * 
     * @return finished emptying queue with error message
     */
    void* pg_harvest_measurements(void *cfg);
    
    /** @brief Enable JavaScript functionality for perf-gear
     * 
     * If you want to use JS for scripting you can register
     * the functions that enable global objecst such as 
     * PerfGear and Measurement to be able to instrument your
     * code easier.
     * 
     * @param ctx
     * @return 
     */
    PG_PUBLIC_API pg_err_t pg_register_js_functions(duk_context *ctx);



#ifdef	__cplusplus
}
#endif

#define PG_INIT() pg_init()
#define PG_COLLECT(x) pg_collect(x)
#define PG_START(x) pg_start(x)
#define PG_STOP() pg_stop()
#define PG_NEW_MEASUREMENT(x, y) pg_new_measurement(x, y) // returns measurement item
#define PG_STOP_COLLECTING(x) pg_stop_collecting(x)
#define PG_INCREASE_HIT(x) pg_increase_hit(x)
#define PG_SAVE_TIMESTAMP(x) pg_save_timestamp(x)
#define PG_SAVE_TIMESTAMP_TAG(x, y) pg_save_timestamp_tag(x, y)
#define PG_SAVE_RAM_USAGE(x) pg_save_ram_usage(x)
#define PG_SAVE_RAM_USAGE_TAG(x, y) pg_save_ram_usage_tag(x, y)

/* MACROS */
#define PG_AUTO_HIT(x) pg_increase_hit(pg_new_measurement(x, PG_MEASUREMENT_TYPE_HIT))
#define PG_AUTO_TIMESTAMP(x) pg_save_timestamp(pg_new_measurement(x, PG_MEASUREMENT_TYPE_TIME))
#define PG_AUTO_TIMESTAMP_TAG(x, y) pg_save_timestamp_tag(pg_new_measurement(x, PG_MEASUREMENT_TYPE_TIME), y)
#define PG_AUTO_RAM(x) pg_save_ram_usage(pg_new_measurement(x, PG_MEASUREMENT_TYPE_RAM))
#define PG_AUTO_RAM_TAG(x, y) pg_save_ram_usage_tag(pg_new_measurement(x, PG_MEASUREMENT_TYPE_RAM), y)



#endif	/* PERF_GEAR_H */

