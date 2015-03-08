/* 
 * File:   collector.h
 * Author: a
 *
 * Created on March 8, 2015, 11:29 AM
 */

#ifndef COLLECTOR_H
#define	COLLECTOR_H

#include "queue.h"

#ifdef	__cplusplus
extern "C" {
#endif

    extern struct pg_measurement_item* pg_start_collecting(char *path, char type);


#ifdef	__cplusplus
}
#endif

#endif	/* COLLECTOR_H */

