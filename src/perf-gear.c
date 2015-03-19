// file: perf-gear.h
#include "perf-gear.h"

pg_err_t pg_harvest_measurements(pg_config_t config) {

    pg_harvest = true;
    int repeat = config->repeat;
    bool infinite_rep = repeat == 0 ? true : false;

    while (pg_harvest && (infinite_rep || repeat-- > 0)) {
        pg_q_item_t qitem = pg_dequeue();
        if (!qitem) continue;
        pg_m_item_t m = qitem->measurement;
        if (!m) continue;

        char *json_result = pg_m2j_transform(m);
        char *file_name = pg_build_filename(m->path, config);
        if (!file_name) perror("Could not measurement filename! It will get lost.");

        pg_err_t result = pg_dsp_save_to_disk(file_name, json_result);
        if (result != PG_NO_ERROR) perror("Could not dispatch measurement! It will get lost.");

        /* cleaning up */
        if (json_result) free(json_result);
        if (file_name) free(file_name);
        pg_destroy_queue_item(qitem);

        /* sleep some time */
        nanosleep((struct timespec[]) {
            {0, HARVEST_WAIT_100MS}
        }, NULL);
        pg_harvest = false; // TODO: finish this
    }

    return PG_NO_ERROR;
}
