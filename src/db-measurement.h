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
    duk_ret_t pg_br_Measurement(duk_context *ctx);

    /** @brief Increase hit counter for this measurement.
     * 
     * @param ctx
     * @return void
     */
    duk_ret_t pg_br_measurement_hit(duk_context *ctx);

    /** @brief Saves the timestamp so that it could be used for deltas.
     * 
     * Timestamps are saved into the sequence array in the object and depending
     * on the measurement time it can be used for measuring the difference between
     * A and B or for sequence display.
     * 
     * @param ctx
     * @return true if saved successfully
     */
    duk_ret_t pg_br_measurement_save_timestamp(duk_context *ctx);
    
    /** @brief Saves the RAM usage for the current moment. It will
     * be associated with a timestamp to match the both.
     * 
     * @param ctx
     * @return 
     */
    duk_ret_t pg_br_measurement_save_ram_usage(duk_context *ctx);

    /** @brief Publish this measurement when done collecting.
     * 
     * @param ctx
     * @return true if successfully published
     */
    duk_ret_t pg_br_measurement_publish(duk_context *ctx);
    
    /** @brief Add dynamic parameters to measurement
     * 
     * Called before publishing in order to serialize all parameters.
     * 
     * @param ctx
     * @param m
     * @return 
     */
    pg_err_t pg_br_msrt_add_params(duk_context *ctx, pg_m_item_t * m);


#ifdef	__cplusplus
}
#endif

#endif	/* DB_MEASUREMENT_H */

