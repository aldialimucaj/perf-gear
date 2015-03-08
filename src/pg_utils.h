/* 
 * File:   pg_utils.h
 * Author: a
 *
 * Created on March 8, 2015, 12:08 PM
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


#ifdef	__cplusplus
}
#endif

#endif	/* PG_UTILS_H */

