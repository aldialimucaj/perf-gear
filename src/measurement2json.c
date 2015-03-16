// file: measurement2json.c

#include "measurement2json.h"

char* pg_transform_seq_json(const pg_mseq_t seq) {
    if (!seq) return NULL;
    int ch_written = snprintf(NULL, 0, PG_TEMPLATE_JSON_SEQ, seq->timestamp, seq->value) + 1;
    char *result = malloc(sizeof (char)*ch_written);
    ch_written = snprintf(result, ch_written, PG_TEMPLATE_JSON_SEQ, seq->timestamp, seq->value);

    return result;
}
