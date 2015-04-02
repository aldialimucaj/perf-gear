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

#ifdef	__cplusplus
extern "C" {
#endif

    void pg_say_hello(void);
    
    int adder(duk_context *ctx);


#ifdef	__cplusplus
}
#endif

#endif	/* DUKBRIDGE_H */

