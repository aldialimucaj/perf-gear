// file: perf-gear.c

#include "perf-gear.h"

bool pg_harvest = false;
pthread_t harvester_th = 0;
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

    pg_harvest = true;
    pg_config_t *cfg = pg_copy_config(config);
    int rc = pthread_create(&harvester_th, NULL, &pg_harvest_measurements, cfg);
    if (rc != 0) perror("Could not start harvester thread.");

    return PG_NO_ERROR;
}

/* ========================================================================= */

pg_err_t pg_stop() {
    pg_err_t r;
    /* we cant stop without emptying the queue */
    while (pg_get_queue_size() != 0) {
    }
    /* this flag turns of the harvester loop */
    pg_harvest = false;
    if (!harvester_th) return PG_ERR_HARVESTER_HAS_NOT_STARTED;
    int h_err;
    int thj_result = pthread_join(harvester_th, (void**) &h_err);
    if (thj_result != 0) perror("Cant wait for harvester thread.");

    size_t q_size = pg_clear_queue();
    if (q_size != 0) return PG_ERR_COULD_NOT_STOP;
    r = pg_destroy_queue();
    if (r != PG_NO_ERROR) return PG_ERR_COULD_NOT_STOP;

    return PG_NO_ERROR;
}

/* ========================================================================= */

void* pg_harvest_measurements(void *cfg) {
    pg_config_t *config = cfg;
    pg_harvest = true;
    int repeat = config->repeat;
    bool infinite_rep = repeat == 0 ? true : false;

    while (pg_harvest && (infinite_rep || repeat-- > 0)) {

        /* sleep some time */
        nanosleep((struct timespec[]) {
            {0, HARVEST_WAIT_100MS}
        }, NULL);

        pg_q_item_t *qitem = pg_dequeue();
        if (!qitem) continue;
        pg_m_item_t *m = qitem->measurement;
        if (!m) continue;

        char *json_result = pg_m2j_transform(m);
        char *file_name = pg_build_filename(m->path, config);
        if (!file_name) perror("Could not create measurement filename! It will get lost.");

        pg_err_t result = pg_dsp_save_to_disk(file_name, json_result);
        if (result != PG_NO_ERROR) perror("Could not dispatch measurement! It will get lost.");

        /* cleaning up */
        if (json_result) free(json_result);
        if (file_name) free(file_name);
        pg_destroy_queue_item(qitem);
    }
    
    pg_destroy_config(config);
    
    return NULL;
}

/* ========================================================================= */

pg_err_t pg_register_js_functions(duk_context *ctx) {
    if(ctx == NULL) return PG_ERR_BAD_ARG;
    
    return dukopen_perf_gear(ctx);
}
