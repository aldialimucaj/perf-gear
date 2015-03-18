// file: measurement2json.c

#include "measurement2json.h"

char* pg_m2j_transform(const pg_m_item_t measurement) {
    if (!measurement) return NULL;
    
    char *seq_json = pg_m2j_seq2json_array(measurement);
    
    /* we don't yet know how much space the buffer needs, so we count.*/
    int ch_written = snprintf(NULL, 0, PG_TEMPLATE_JSON_MESRNT,
            measurement->path,
            measurement->type,
            measurement->hitValue,
            seq_json
            ) + 1;
    /* after learning the the exact size of the json string, we can create the buffer */
    char *result = malloc(sizeof (char)*ch_written);
    ch_written = snprintf(result, ch_written, PG_TEMPLATE_JSON_MESRNT,
            measurement->path,
            measurement->type,
            measurement->hitValue,
            seq_json
            );
    
    /* no need for seq array anymore */
    free(seq_json);
    
    return result;
}

/* ========================================================================= */

char* pg_transform_seq_json(const pg_mseq_t seq) {
    if (!seq) return NULL;
    int ch_written = snprintf(NULL, 0, PG_TEMPLATE_JSON_SEQ, seq->timestamp, seq->value) + 1;
    char *result = malloc(sizeof (char)*ch_written);
    ch_written = snprintf(result, ch_written, PG_TEMPLATE_JSON_SEQ, seq->timestamp, seq->value);

    return result;
}

/* ========================================================================= */

char* pg_m2j_seq2json_array(const pg_m_item_t m) {
    if (!m) return NULL;
    if (!m->sequence) return strdup("[]");

    char *result = NULL;
    pg_mseq_t seq = m->sequence;

    while (seq) {
        char *current_seq_json = pg_transform_seq_json(seq);
        if (!result) {
            result = strdup(current_seq_json);
        } else {
            int alloc_size1 = strlen(result);
            /* size of current seq + 1 for the termination char */
            int alloc_size2 = strlen(current_seq_json) + 1;
            /* comma separated elements in array ',' 1 char */
            int other_chars = 1;


            char *new_result = malloc(alloc_size1 + alloc_size2 + other_chars);
            strcpy(new_result, result);
            strcat(new_result, ",");
            strcat(new_result, current_seq_json);

            /* free old result */
            free(result);
            result = new_result;
        }
        free(current_seq_json);

        seq = seq->next;
    }
    /* at this point we add the square brackets + termination */
    int arr_size = strlen(result) + 3;
    char *json_array = malloc(sizeof(char)*arr_size);
    strcpy(json_array,"[");
    strcat(json_array,result);
    strcat(json_array,"]");
    
    free(result);
    result = json_array;

    return result;
}