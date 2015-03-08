#include "collector.h"

extern struct pg_measurement_item* pg_start_collecting(char *path, pg_mtype_t type) {
    if (!path) return NULL; /* no path */
    if (type <= PG_MEASUREMENT_TYPE_UNKNOWN) return NULL; /* no type */
    struct pg_measurement_item* measurement = pg_create_measurement_item();
    /* if no path allocate the new one */
    if (!measurement->path) {
        size_t length = sizeof (char)*(strlen(path) + 1);
        measurement->path = strncpy(measurement->path, path, length);
    }

    /* set the type */
    measurement->type = type;

    return measurement;
}