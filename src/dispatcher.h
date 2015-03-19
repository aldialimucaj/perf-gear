/** @brief Sends measurement content to different endpoints. 
 * 
 * @file dispatcher.h
 * @author Aldi Alimucaj
 *
 * @date March 17, 2015, 8:30 PM
 * 
 * Sharing content with other systems or saving into hard drive.
 * 
 */

#ifndef DISPATCHER_H
#define	DISPATCHER_H

#include <stdio.h>
#include "pg-utils.h"
#include "queue.h"

#ifdef	__cplusplus
extern "C" {
#endif

    /** @brief Save measurement content to disk
     * 
     * @param path
     * @param content
     * 
     * @return Result of saving operation
     */
    pg_err_t pg_dsp_save_to_disk(char *path, char *content);



#ifdef	__cplusplus
}
#endif

#endif	/* DISPATCHER_H */

