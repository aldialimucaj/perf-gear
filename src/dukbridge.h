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

    duk_ret_t pg_br_startPerfGear(duk_context *ctx);
    
    void pg_say_hello(duk_context *ctx);
    
    int adder(duk_context *ctx);
    
    /** @brief Register all perf gear functions
     * 
     * Registers c functions
     * 
     * @param ctx
     * @return 
     */
    pg_err_t pg_br_register_functions(duk_context *ctx);
    



#ifdef	__cplusplus
}
#endif

#endif	/* DUKBRIDGE_H */

