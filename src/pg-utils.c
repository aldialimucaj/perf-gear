// file: pg_utils.c

#include "pg-utils.h"
#include "collector.h"

char* pg_build_filename(char* filename, pg_config_t config) {
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