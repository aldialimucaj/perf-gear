/** @brief C Implementation of PGMeasurement object in JS
 *  
 * @file db-measurement.h
 * @author Aldi Alimucaj
 *
 * @date May 29, 2015, 3:46 PM
 * 
 * Bridge between JS and perf-gear measurement.
 */

#ifndef DB_MEASUREMENT_H
#define	DB_MEASUREMENT_H

#include "../lib/duktape.h"
#include "perf-gear.h"
#include "collector.h"

#ifdef	__cplusplus
extern "C" {
#endif

    /** @brief Constructor for PGMeasurment.
     * 
     * @param ctx
     * @return object
     */
    duk_ret_t pg_br_PGMeasurement(duk_context *ctx);

    /** @brief Publish this measurement when done collecting.
     * 
     * @param ctx
     * @return true if successfully published
     */
    duk_ret_t pg_br_publish_measurement(duk_context *ctx);
    

#ifdef	__cplusplus
}
#endif

#endif	/* DB_MEASUREMENT_H */

