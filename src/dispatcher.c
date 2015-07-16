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

/* ========================================================================= */

pg_err_t pg_net_post(const char* url, const char* json) {
    pg_err_t err = PG_NO_ERROR;
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers = NULL;

    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

    /* get a curl handle */
    curl = curl_easy_init();
    if (curl) {
        /* set content type */
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");

        /* First set the URL that is about to receive our POST. This URL can
           just as well be a https:// URL if that is what should receive the
           data. */
        curl_easy_setopt(curl, CURLOPT_URL, url);
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK) {
            fprintf(stderr, "Sending data failed: %s\n", curl_easy_strerror(res));
            err = PG_ERR_SENDING_JSON;
        }

        /* free headers */
        curl_slist_free_all(headers);
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return err;
}