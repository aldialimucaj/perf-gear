/* 
 * File:   perf-gear-stubs.h
 * Author: a
 *
 * Created on September 19, 2015, 3:59 PM
 */

#ifndef PERF_GEAR_STUBS_H
#define	PERF_GEAR_STUBS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define PG_INIT() 
#define PG_COLLECT(x)
#define PG_START(x) 
#define PG_STOP() 
#define PG_NEW_MEASUREMENT(x, y) NULL // returns measurement item
#define PG_STOP_COLLECTING(x) 
#define PG_INCREASE_HIT(x) 
#define PG_SAVE_TIMESTAMP(x) 
#define PG_SAVE_TIMESTAMP_TAG(x, y) 
#define PG_SAVE_RAM_USAGE(x) 
#define PG_SAVE_RAM_USAGE_TAG(x, y) 

#ifdef	__cplusplus
}
#endif

#endif	/* PERF_GEAR_STUBS_H */

