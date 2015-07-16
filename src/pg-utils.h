/** 
 * @file pg_utils.h
 * @author Aldi Alimucaj
 *
 * @date March 8, 2015, 12:08 PM
 */

#ifndef PG_UTILS_H
#define	PG_UTILS_H

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE	199309L
#endif

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <curl/curl.h>


#define PG_FN_REPACE_CHR_FROM '/'
#define PG_FN_REPACE_CHR_TO "_"

#ifdef	__cplusplus
extern "C" {
#endif

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
        PG_ERR_MEASUREMENT_UNIT_CANT_CHANGE, /*!< Measurement unit is set and cant be changed */
        PG_ERR_NO_MEASUREMENT_SEQ, /*!< No measurement sequences were passed */
        PG_ERR_NO_MEASUREMENT_PARAM, /*!< No measurement parameters were passed */
        PG_ERR_QUEUE_NOT_READY, /*!< Queue is NULL or not ready */
        PG_ERR_QUEUE_NOT_EMPTY, /*!< Cannot destroy queue with elements */
        PG_ERR_NO_SOURCE, /*!< No correct source was passed */
        PG_ERR_NO_DESTINATION, /*!< No correct destination was passed */
        PG_ERR_NO_DES_PATH, /*!< No destination file path to write to */
        PG_ERR_COULD_NOT_OPEN_PATH, /*!< Could not open file path with write permissions */
        PG_ERR_NO_CONTENT, /*!< No content to write about */
        PG_ERR_HARVESTER_HAS_NOT_STARTED, /*!< */
        PG_ERR_REGISTER_FUNC, /*!< Error registering bridge functions */
        PG_ERR_COULD_NOT_START, /*!< Could not start perf gear */
        PG_ERR_COULD_NOT_STOP, /*!< Could not stop perf gear properly*/
        PG_ERR_SENDING_JSON, /*!< Could not send json data to the server */
        PG_ERR_, /*!< */
        PG_ERR_BAD_ARG, /*!< Bad or NULL argument */
        PG_ERR_UNKNOWN_ERROR /*!< Uncategorized error occured */
    } pg_err_t;

    /** @brief Configuration for measurement storage and formatting
     * 
     */
    typedef struct pg_config {
        char* folder; /*!< Where to store the reuslts */
        char* result_name_prefix; /*!< Prefix like PRE_#path#.json */
        char* result_name_suffix; /*!< Suffix like #path#_SUF.json */
        char* url; /*!< URL to post measurement if present */
        int repeat; /*!< how many times to fetch before stopping. 0=Infinite */
    } pg_config_t;

    /** @brief Creates a file name compatible with fs.
     * 
     * @param filename
     * @param config
     * @return 
     */
    char* pg_build_filename(char* filename, pg_config_t *config);


    /** @brief Checks if the string matches in the end
     * 
     * Courtesy of plinth[at]stackoverflow
     * 
     * @param str
     * @param suffix
     * @return 
     */
    bool pg_str_ends_with(const char *str, const char *suffix);

    /** @brief Replace char ch in source with repl and return new string.
     * 
     * Courtesy of nneonneo[at]stackoverflow
     * 
     * @param src
     * @param ch
     * @param repl
     * @return 
     */
    char *pg_str_replace(const char *src, char ch, const char *repl);

    /** @brief Create directory recursively
     * 
     * courtesy of http://nion.modprobe.de/blog/archives/357-Recursive-directory-creation.html
     * 
     * @param dir
     */
    void pg_mkdir(const char *dir);

    /** @brief Allocate config object
     * 
     * @return 
     */
    pg_config_t* pg_create_config(void);

    /** @brief Free config and all its content
     * 
     * @param config
     * @return 
     */
    pg_err_t pg_destroy_config(pg_config_t *config);

    /** @brief Clone config
     * 
     * @return 
     */
    pg_config_t* pg_copy_config(pg_config_t* cfg);

    /** @brief Get the Unix time in seconds.
     * 
     * @return 
     */
    unsigned long long pg_get_timestamp();
    
    /** @brief Get the Unix time in milliseconds.
     * 
     * @return 
     */
    unsigned long long pg_get_timestamp_msec();
    
    /** @brief Get the Unix time in microseconds.
     * 
     * @return 
     */
    unsigned long long pg_get_timestamp_usec();
    
    /** @brief Match unit id to physical name.
     * 
     * @param 
     * @return 
     */
    char* pg_get_str_unit(char unit);

    /* ========================================================================= */
    /* SYSTEM UTILS */
    /* ========================================================================= */

    /** @brief Reallocate memory and set the new offset to zero.
     * 
     * Credit: JaredPar @ StackOverflow
     * 
     * @param pBuffer
     * @param oldSize
     * @param newSize
     * @return 
     */
    void* pg_realloc_zero(void* pBuffer, size_t oldSize, size_t newSize);


    /* ========================================================================= */
    /* EXTERNALS */
    /* ========================================================================= */

    extern char *strdup(const char *s);






#ifdef	__cplusplus
}
#endif

#endif	/* PG_UTILS_H */

