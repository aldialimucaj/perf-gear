/** @brief Connecting Perf Gear to Duktape
 * 
 * @file   queue.h
 * @author Aldi Alimucaj
 *
 * @date March 30, 2015, 10:33 AM
 * 
 * Accessing duktape function calls and stack manipulation.
 * 
 */
#ifndef DUKBRIDGE_H
#define	DUKBRIDGE_H

#include "../lib/duktape.h"
#include "perf-gear.h"
#include "collector.h"
#include "pg-utils.h"

#ifdef	__cplusplus
extern "C" {
#endif
    

    /** @brief Start collecting
     * 
     * @param ctx
     * @return 
     */
    duk_ret_t pg_br_startPerfGear(duk_context *ctx);
    
    /** @brief Stop collecting
     * 
     * @param ctx
     * @return 
     */
    duk_ret_t pg_br_stopPerfGear(duk_context *ctx);
    
    /** @brief Measurement object
     * 
     * @param ctx
     * @return 
     */
    duk_ret_t pg_br_measurement(duk_context *ctx);
    
    /** @brief Register all perf gear functions
     * 
     * Registers c functions
     * 
     * @param ctx
     * @return 
     */
    duk_ret_t dukopen_perf_gear(duk_context *ctx);
    



#ifdef	__cplusplus
}
#endif

#endif	/* DUKBRIDGE_H */

