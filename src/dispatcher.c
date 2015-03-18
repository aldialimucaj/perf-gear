// file: dispatcher.c
#include "dispatcher.h"

pg_err_t pg_dsp_save_to_disk(char *path, char *content) {
    if (!path) return PG_ERR_NO_DES_PATH;
    if (!content) return PG_ERR_NO_CONTENT;

    FILE *fp = fopen(path, "w");
    if (!fp) return PG_ERR_COULD_NOT_OPEN_PATH;

    fprintf(fp, content, NULL);

    int result = fclose(fp);
    return result == 0 ? PG_NO_ERROR : PG_ERR_UNKNOWN_ERROR;
}
