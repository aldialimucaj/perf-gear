// file: measurement2json.c

#include "measurement2json.h"

char* pg_m2j_transform(const pg_m_item_t *measurement) {
    if (!measurement) return NULL;

    char *seq_json = pg_m2j_seq2json_array(measurement);
    char *param_json = NULL;
    if (measurement->param) param_json = pg_m2j_param2json(measurement->param);
    /* add the extra ending comma */
    if (param_json) {
        size_t pj_len = strlen(param_json);
        param_json = pg_realloc_zero(param_json, pj_len, pj_len + 2);
        strcat(param_json, ",");
    } else { // else just an empty string to match the printf params
        param_json = strdup("");
    }
    /* we don't yet know how much space the buffer needs, so we count.*/
    int ch_written = snprintf(NULL, 0, PG_TEMPLATE_JSON_MESRNT,
            measurement->path,
            measurement->type,
            measurement->hitValue,
            param_json,
            seq_json
            ) + 1;
    /* after learning the the exact size of the JSON string, we can create the buffer */
    char *result = malloc(sizeof (char)*ch_written);
    snprintf(result, ch_written, PG_TEMPLATE_JSON_MESRNT,
            measurement->path,
            measurement->type,
            measurement->hitValue,
            param_json,
            seq_json
            );

    /* no need for seq array anymore */
    free(seq_json);
    free(param_json);

    return result;
}

/* ========================================================================= */

char* pg_transform_seq_json(const pg_mseq_t *seq) {
    if (!seq) return NULL;
    char *result = NULL;
    if (seq->tag) {
        int ch_written = snprintf(NULL, 0, PG_TEMPLATE_JSON_SEQ_W_TAG, seq->timestamp, seq->value, seq->tag) + 1;
        result = malloc(sizeof (char)*ch_written);
        snprintf(result, ch_written, PG_TEMPLATE_JSON_SEQ_W_TAG, seq->timestamp, seq->value, seq->tag);
    } else {
        int ch_written = snprintf(NULL, 0, PG_TEMPLATE_JSON_SEQ, seq->timestamp, seq->value) + 1;
        result = malloc(sizeof (char)*ch_written);
        snprintf(result, ch_written, PG_TEMPLATE_JSON_SEQ, seq->timestamp, seq->value);
    }

    return result;
}

/* ========================================================================= */

char* pg_m2j_seq2json_array(const pg_m_item_t *m) {
    if (!m) return NULL;
    if (!m->sequence) return strdup("[]");

    char *result = NULL;
    pg_mseq_t *seq = m->sequence;

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
    char *json_array = malloc(sizeof (char)*arr_size);
    strcpy(json_array, "[");
    strcat(json_array, result);
    strcat(json_array, "]");

    free(result);
    result = json_array;

    return result;
}

/* ========================================================================= */

char* pg_m2j_param2json(pg_m_param_t *param) {
    if (!param) return NULL;
    char *result = NULL;
    pg_m_param_t *p = param;
    /* size of the current buffer */
    size_t alloc_size = 0;
    size_t old_alloc_size = 0;
    while (p) {
        /* buffer for the current parameter */
        char *json_param = NULL;

        switch (p->type) {
            case PG_PARAM_TYPE_STR:
                if (p->strValue) {
                    int ch_written = snprintf(
                            NULL, 0, PG_TEMPLATE_JSON_PARAM_STR, p->key, p->strValue) + 1;
                    json_param = malloc(sizeof (char)*ch_written);
                    snprintf(json_param, ch_written, PG_TEMPLATE_JSON_PARAM_STR, p->key, p->strValue);

                    alloc_size += ch_written;
                }
                break;
            case PG_PARAM_TYPE_OBJ:
                if (p->objValue) {
                    char *json_obj = pg_m2j_param2json(p->objValue);
                    int ch_written = snprintf(
                            NULL, 0, PG_TEMPLATE_JSON_PARAM_OBJ, p->key, json_obj) + 1;
                    json_param = malloc(sizeof (char)*ch_written);
                    snprintf(json_param, ch_written, PG_TEMPLATE_JSON_PARAM_OBJ, p->key, json_obj);

                    alloc_size += ch_written;
                    free(json_obj);
                }
                break;
            default:
                json_param = strdup("\"err\":\"Unsupported parameter\"");
                alloc_size += strlen(json_param) + 1;
                break;
        }
        /* if parameter list is not empty we need to add a comma */
        if (p->next) {
            alloc_size++;
            size_t jp_len = strlen(json_param);
            json_param = pg_realloc_zero(json_param, jp_len, jp_len + 2);
            strcat(json_param, ",");
        }
        result = pg_realloc_zero(result, old_alloc_size, alloc_size);
        old_alloc_size = alloc_size;
        if (json_param) {
            strcat(result, json_param);
            free(json_param);
            json_param = NULL;
        }
        /* go to the next parameter */
        p = p->next;
    }

    return result;
}