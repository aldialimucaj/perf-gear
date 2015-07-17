// file: perf-gear.c

#include "perf-gear.h"

volatile bool pg_harvest = false;
pthread_attr_t attr;
pthread_t harvester_th = 0;
pthread_mutex_t pg_q_mutex;
duk_context *duk_ctx = NULL;

pg_err_t pg_init() {
    struct pg_queue* q = pg_init_queue();
    if (q == NULL) return PG_ERR_COULD_NOT_START;

    return PG_NO_ERROR;
}

/* ========================================================================= */

pg_err_t pg_collect(pg_config_t *config) {
    return pg_start(config);
}

/* ========================================================================= */

pg_err_t pg_start(pg_config_t *config) {
    struct pg_queue* q = pg_init_queue();
    if (q == NULL) return PG_ERR_COULD_NOT_START;
    /* init mutex */
    pthread_mutex_init(&pg_q_mutex, NULL);
    /* thread attributes -> make it joinable */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    /* lock */
    pthread_mutex_lock(&pg_q_mutex);
    pg_harvest = true;
    /* release mutex */
    pthread_mutex_unlock(&pg_q_mutex);
    
    pg_config_t *cfg = pg_copy_config(config);
    int rc = pthread_create(&harvester_th, &attr, &pg_harvest_measurements, cfg);
    if (rc != 0) perror("Could not start harvester thread.");
    /* destroy mutex attributes */
    pthread_attr_destroy(&attr);

    return PG_NO_ERROR;
}

/* ========================================================================= */

pg_err_t pg_stop() {
    pg_err_t r;
    /* lock */
    pthread_mutex_lock(&pg_q_mutex);
    /* this flag turns of the harvester loop */
    pg_harvest = false;
    /* release mutex */
    pthread_mutex_unlock(&pg_q_mutex);
    if (!harvester_th) return PG_ERR_HARVESTER_HAS_NOT_STARTED;
    int h_err;
    int thj_result = pthread_join(harvester_th, (void**) &h_err);
    if (thj_result != 0) perror("Cant wait for harvester thread.");

    /* just in case harvester didn't empty the queue */
    size_t q_size = pg_clear_queue();
    if (q_size != 0) return PG_ERR_COULD_NOT_STOP;
    r = pg_destroy_queue();
    if (r != PG_NO_ERROR) return PG_ERR_COULD_NOT_STOP;

    /* destroy mutex */
    pthread_mutex_destroy(&pg_q_mutex);
    return PG_NO_ERROR;
}

/* ========================================================================= */

void* pg_harvest_measurements(void *cfg) {
    pg_config_t *config = cfg;

    while (pg_harvest || pg_get_queue_size() != 0) {
        /* retrieve element from queue. function is thread safe */
        pg_q_item_t *qitem = pg_dequeue();
        if (!qitem) {

            /* sleep some time */
            nanosleep((struct timespec[]) {
                {0, HARVEST_WAIT_10MS}
            }, NULL);
            continue;
        }
        pg_m_item_t *m = qitem->measurement;
        if (!m) continue;

        /* forward to dispatcher */
        pg_dsp_persist(config, m);

        /* cleaning up */
        pg_destroy_queue_item(qitem);
    }

    pg_destroy_config(config);

    return NULL;
}

/* ========================================================================= */

pg_err_t pg_register_js_functions(duk_context *ctx) {
    if (ctx == NULL) return PG_ERR_BAD_ARG;

    return dukopen_perf_gear(ctx);
}
