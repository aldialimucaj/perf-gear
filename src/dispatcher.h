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
    
    /* ========================================================================= */
    /* NET UTILS */
    /* ========================================================================= */

    /** @brief Send HTTP POST request to url with json payload.
     * 
     * Using libcurl http://curl.haxx.se/libcurl/c/http-post.html 
     * 
     * @param url
     * @param json
     * @return 
     */
    pg_err_t pg_net_post(const char* url, const char* json);



#ifdef	__cplusplus
}
#endif

#endif	/* DISPATCHER_H */

