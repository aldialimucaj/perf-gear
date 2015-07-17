// file: pg_utils.c

#include <stdio.h>
#include <sys/time.h>
#include "pg-utils.h"
#include "collector.h"

char* pg_build_filename(char* filename, pg_config_t *config) {
    if (!filename) return NULL;
    char *result = NULL;
    size_t fn_len = strlen(filename);
    size_t folder_len = 0;
    bool add_folder = false;
    bool add_slash = false;

    if (config && config->folder) {
        add_folder = true;
        pg_mkdir(config->folder);
        folder_len = strlen(config->folder) + 1;
        if (!pg_str_ends_with(config->folder, "/")) {
            folder_len++;
            add_slash = true;
        }
    }

    char *escaped_fn = pg_str_replace(filename, PG_FN_REPACE_CHR_FROM, PG_FN_REPACE_CHR_TO);

    /* 5 = .json + 1 = \0 */
    result = malloc(sizeof (char) * (fn_len + folder_len + 5 + 1));
    if (add_folder) strcpy(result, config->folder);
    if (add_slash) strcat(result, "/");
    strcat(result, escaped_fn);
    strcat(result, ".json");

    free(escaped_fn);

    return result;
}

/* ========================================================================= */

bool pg_str_ends_with(const char *str, const char *suffix) {
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix > lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

/* ========================================================================= */

char *pg_str_replace(const char *s, char ch, const char *repl) {
    int count = 0;
    const char *t;
    for (t = s; *t; t++)
        count += (*t == ch);

    size_t rlen = strlen(repl);
    char *res = malloc(strlen(s) + (rlen - 1) * count + 1);
    char *ptr = res;
    for (t = s; *t; t++) {
        if (*t == ch) {
            memcpy(ptr, repl, rlen);
            ptr += rlen;
        } else {
            *ptr++ = *t;
        }
    }
    *ptr = 0;
    return res;
}

/* ========================================================================= */

void pg_mkdir(const char *dir) {
    char tmp[256];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof (tmp), "%s", dir);
    len = strlen(tmp);
    if (tmp[len - 1] == '/') {
        tmp[len - 1] = 0;
    }
    for (p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = 0;
            mkdir(tmp, S_IRWXU);
            *p = '/';
        }
    }
    mkdir(tmp, S_IRWXU);
}

/* ========================================================================= */

pg_config_t* pg_create_config(void) {
    pg_config_t *c = malloc(sizeof (pg_config_t));
    c->folder = NULL;
    c->result_name_prefix = NULL;
    c->result_name_suffix = NULL;
    c->url = NULL;
    c->repeat = 0;

    return c;
}

/* ========================================================================= */

pg_err_t pg_destroy_config(pg_config_t *config) {
    if (config == NULL) return PG_ERR_BAD_ARG;
    if (config->folder) free(config->folder);
    if (config->result_name_prefix) free(config->result_name_prefix);
    if (config->result_name_suffix) free(config->result_name_suffix);
    if (config->url) free(config->url);
    free(config);

    return PG_NO_ERROR;
}

/* ========================================================================= */

pg_config_t* pg_copy_config(pg_config_t* cfg) {
    if (cfg == NULL) return NULL;
    pg_config_t *c = pg_create_config();
    if (cfg->folder) c->folder = strdup(cfg->folder);
    if (cfg->url) c->url = strdup(cfg->url);
    if (cfg->result_name_prefix) c->result_name_prefix = strdup(cfg->result_name_prefix);
    if (cfg->result_name_suffix) c->result_name_suffix = strdup(cfg->result_name_suffix);
    c->repeat = cfg->repeat;

    return c;
}

/* ========================================================================= */

void* pg_realloc_zero(void* pBuffer, size_t oldSize, size_t newSize) {
    void* pNew = realloc(pBuffer, newSize);
    if (newSize > oldSize && pNew) {
        size_t diff = newSize - oldSize;
        void* pStart = ((char*) pNew) + oldSize;
        memset(pStart, 0, diff);
    }
    return pNew;
}

/* ========================================================================= */

unsigned long long pg_get_timestamp() {
    struct timeval tv;

    gettimeofday(&tv, NULL);

    unsigned long long millisecondsSinceEpoch =
            (unsigned long long) (tv.tv_sec);

    return millisecondsSinceEpoch;
}

/* ========================================================================= */

unsigned long long pg_get_timestamp_msec() {
    struct timeval tv;

    gettimeofday(&tv, NULL);

    unsigned long long millisecondsSinceEpoch =
            (unsigned long long) (tv.tv_sec) * 1000 +
            (unsigned long long) (tv.tv_usec) / 1000;

    return millisecondsSinceEpoch;
}

/* ========================================================================= */

unsigned long long pg_get_timestamp_usec() {
    struct timeval tv;

    gettimeofday(&tv, NULL);

    unsigned long long microsecondsSinceEpoch =
            (unsigned long long) (tv.tv_sec) * 1000000 +
            (unsigned long long) (tv.tv_usec);

    return microsecondsSinceEpoch;
}

/* ========================================================================= */

char* pg_get_str_unit(char unit) {
    char *unit_str = NULL;
    switch (unit) {
        case PG_MEASUREMENT_UNIT_HIT:
            unit_str = "HITS";
            break;
        case PG_MEASUREMENT_UNIT_US:
            unit_str = "MICROSECONDS";
            break;
        case PG_MEASUREMENT_UNIT_MS:
            unit_str = "MILLISECONDS";
            break;
        case PG_MEASUREMENT_UNIT_S:
            unit_str = "SECONDS";
            break;
        case PG_MEASUREMENT_UNIT_BT:
            unit_str = "BYTE";
            break;
        case PG_MEASUREMENT_UNIT_KB:
            unit_str = "KIBIBYTE";
            break;
        case PG_MEASUREMENT_UNIT_MB:
            unit_str = "MEBIBYTE";
            break;
        default:
            unit_str = "UNKOWN";
    }
    return unit_str;
}

/* ========================================================================= */

char* pg_get_str_m_type(char typeId) {
    char *type_str = NULL;
    switch (typeId) {
        case PG_MEASUREMENT_TYPE_HIT:
            type_str = "HIT";
            break;
        case PG_MEASUREMENT_TYPE_TIME:
            type_str = "TIME";
            break;
        case PG_MEASUREMENT_TYPE_RAM:
            type_str = "RAM";
            break;
        default:
            type_str = "UNKOWN";
    }
    return type_str;
}