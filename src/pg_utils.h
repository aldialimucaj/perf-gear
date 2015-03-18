/** 
 * @file pg_utils.h
 * @author Aldi Alimucaj
 *
 * @date March 8, 2015, 12:08 PM
 */

#ifndef PG_UTILS_H
#define	PG_UTILS_H

#include <string.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define PG_PUBLIC_API __attribute__((__visibility__("default")))

#define PG_STRLEN(x) sizeof(char) * strlen(x) + 1
#define PG_STRDUP strdup

    /** @brief Error types returned by perf-gear functions.
     * 
     */
    typedef enum {
        PG_NO_ERROR = 0, /*!< No Error, everything went fine */
        PG_ERR_COULD_NOT_CREATE, /*!< Count not allocate memore for operation */
        PG_ERR_NO_Q_ITEM, /*!< No queue item passed */
        PG_ERR_NO_MEASUREMENT, /*!< No Measurement */
        PG_ERR_WRONG_MEASUREMENT_TYPE, /*!< Passed wrong measurement type for this operation */
        PG_ERR_NO_MEASUREMENT_SEQ, /*!< No measurement sequences was passed */
        PG_ERR_QUEUE_NOT_READY, /*!< Queue is NULL or not ready */
        PG_ERR_QUEUE_NOT_EMPTY, /*!< Cannot destroy queue with elements */
        PG_ERR_NO_SOURCE, /*!< No correct source was passed */
        PG_ERR_NO_DESTINATION, /*!< No correct destination was passed */
        PG_ERR_NO_DES_PATH, /*!< No destination file path to write to */
        PG_ERR_COULD_NOT_OPEN_PATH, /*!< Could not open file path with write permissions */
        PG_ERR_NO_CONTENT, /*!< No content to write about */
        PG_ERR_, /*!< */
        PG_ERR_UNKNOWN_ERROR /*!< Uncategorized error occured */
    } pg_err_t;


#ifdef	__cplusplus
}
#endif

#endif	/* PG_UTILS_H */

