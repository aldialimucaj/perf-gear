/** @brief Transformation of measurement into JSON
 * 
 * @file    measurement2json.h
 * @author  Aldi Alimucaj
 *
 * @date March 16, 2015, 5:43 PM
 * 
 * Helper functions to transform measurements into JSON
 * data ready to be persisted.
 * 
 */

#ifndef MEASUREMENT2JSON_H
#define	MEASUREMENT2JSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define PG_TEMPLATE_JSON_SEQ "{timestamp:%zd,value:%.2f}"
#define PG_TEMPLATE_JSON_MESRNT "{path:\x22%s\x22,type:%d,hitValue:%zd,sequence:%s}"

#ifdef	__cplusplus
extern "C" {
#endif

    /** @brief Generates a JSON string that matches the the measurement's content.
     * 
     * @param measurement
     * @return Pointer to JSON String
     */
    char* pg_m2j_transform(const pg_m_item_t measurement);

    /** @brief Generates a sequence JSON string
     * 
     * @param seq
     * @return 
     */
    char* pg_transform_seq_json(const pg_mseq_t seq);
    
    /** @brief Generates a sequence of all JSON string and returns them as json array
     * 
     * It retuns all the sequences in this measurement as string
     * @code
     * // m with two sequences
     * char *seq_array = pg_m2j_seq2json_array(v);
     * // will return "[{timestamp:0,value:1}, {timestamp:1,value:2}]"
     * @endcode
     * 
     * @param m
     * @return 
     */
    char* pg_m2j_seq2json_array(const pg_m_item_t m);


#ifdef	__cplusplus
}
#endif

#endif	/* MEASUREMENT2JSON_H */

