#include "collector.h"
#include "pg-utils.h"

pg_m_item_t* pg_new_measurement(const char *path, pg_mtype_t type) {
    if (!path) return NULL; /* no path */
    if (type <= PG_MEASUREMENT_TYPE_UNKNOWN) return NULL; /* no type */

    /* this is the new measurement object that will collect all data */
    pg_m_item_t *measurement = pg_create_measurement_item();
    /* if no path allocate the new one */
    if (!measurement->path) {
        measurement->path = PG_STRDUP(path);
    }

    /* set the type */
    measurement->type = type;

    return measurement;
}

/* ========================================================================= */

pg_err_t pg_stop_collecting(pg_m_item_t *measurement) {
    if (!measurement) return PG_ERR_NO_MEASUREMENT; // no measurement to destroy

    /* publish the results */
    int result = pg_publish_measurement(measurement);

    /* we destroy the measurement anyway */
    if (result || true)
        result = pg_destroy_measurement_item(measurement);

    return result;
}

/* ========================================================================= */

pg_err_t pg_publish_measurement(pg_m_item_t *measurement) {
    if (!measurement) return PG_ERR_NO_MEASUREMENT; // no measurement to destroy

    /* create an item for the queue */
    pg_q_item_t *item = pg_create_queue_item();
    item->measurement = pg_create_measurement_item();

    /* copy the passed measurement */
    pg_err_t result = pg_copy_measurement_item(measurement, item->measurement);

    /* enqueue the item */
    if (result == PG_NO_ERROR)
        result = pg_enqueue(item);

    /* after enqueue we can delete the measurement */
    if (result == PG_NO_ERROR) {
        result = pg_destroy_queue_item(item);
    }

    return result;
}

/* ========================================================================= */

pg_err_t pg_increase_hit(pg_m_item_t *measurement) {
    if (!measurement) return PG_ERR_NO_MEASUREMENT; // nothing to update
    if (measurement->type != PG_MEASUREMENT_TYPE_HIT)
        return PG_ERR_WRONG_MEASUREMENT_TYPE; // wrong type
    /* check if pristine otherwise cant change unit */
    if (measurement->unit == PG_MEASUREMENT_UNIT_UNKNOWN){
        measurement->unit = PG_MEASUREMENT_UNIT_HIT;
    } else if(measurement->unit != PG_MEASUREMENT_UNIT_HIT) {
        return PG_ERR_MEASUREMENT_UNIT_CANT_CHANGE;
    }

    measurement->hitValue++;
    return PG_NO_ERROR;
}

/* ========================================================================= */

pg_err_t pg_save_timestamp(pg_m_item_t *measurement) {
    if (!measurement) return PG_ERR_NO_MEASUREMENT; // nothing to update
    if (measurement->type != PG_MEASUREMENT_TYPE_TIME)
        return PG_ERR_WRONG_MEASUREMENT_TYPE; // wrong type

    /* check if pristine otherwise cant change unit */
    if (measurement->unit == PG_MEASUREMENT_UNIT_UNKNOWN){
        measurement->unit = PG_MEASUREMENT_UNIT_US;
    } else if(measurement->unit != PG_MEASUREMENT_UNIT_US) {
        return PG_ERR_MEASUREMENT_UNIT_CANT_CHANGE;
    }
    
    pg_mseq_t *seq = pg_create_measurement_sequence();
    seq->timestamp = pg_get_timestamp_usec();
    seq->value = 0;
    return pg_add_measurement_sequence(measurement, seq);
}

/* ========================================================================= */

pg_err_t pg_save_timestamp_tag(pg_m_item_t *measurement, const char *tag) {
    if (!measurement) return PG_ERR_NO_MEASUREMENT; // nothing to update
    if (measurement->type != PG_MEASUREMENT_TYPE_TIME)
        return PG_ERR_WRONG_MEASUREMENT_TYPE; // wrong type

    /* check if pristine otherwise cant change unit */
    if (measurement->unit == PG_MEASUREMENT_UNIT_UNKNOWN){
        measurement->unit = PG_MEASUREMENT_UNIT_US;
    } else if(measurement->unit != PG_MEASUREMENT_UNIT_US) {
        return PG_ERR_MEASUREMENT_UNIT_CANT_CHANGE;
    }
    
    pg_mseq_t *seq = pg_create_measurement_sequence();
    seq->timestamp = pg_get_timestamp_usec();
    seq->value = 0;
    seq->tag = PG_STRDUP(tag);
    return pg_add_measurement_sequence(measurement, seq);
}

/* ========================================================================= */

pg_err_t pg_save_ram_usage(pg_m_item_t *measurement) {
    if (!measurement) return PG_ERR_NO_MEASUREMENT; // nothing to update
    if (measurement->type != PG_MEASUREMENT_TYPE_RAM)
        return PG_ERR_WRONG_MEASUREMENT_TYPE; // wrong type

    /* check if pristine otherwise cant change unit */
    if (measurement->unit == PG_MEASUREMENT_UNIT_UNKNOWN){
        measurement->unit = PG_MEASUREMENT_UNIT_KB;
    } else if(measurement->unit != PG_MEASUREMENT_UNIT_KB) {
        return PG_ERR_MEASUREMENT_UNIT_CANT_CHANGE;
    }
    
    pg_mseq_t *seq = pg_create_measurement_sequence();
    seq->timestamp = pg_get_timestamp_usec();
    seq->value = pg_get_ram_usage();
    return pg_add_measurement_sequence(measurement, seq);
}

/* ========================================================================= */

pg_err_t pg_save_ram_usage_tag(pg_m_item_t *measurement, const char *tag) {
    if (!measurement) return PG_ERR_NO_MEASUREMENT; // nothing to update
    if (measurement->type != PG_MEASUREMENT_TYPE_RAM)
        return PG_ERR_WRONG_MEASUREMENT_TYPE; // wrong type

    /* check if pristine otherwise cant change unit */
    if (measurement->unit == PG_MEASUREMENT_UNIT_UNKNOWN){
        measurement->unit = PG_MEASUREMENT_UNIT_KB;
    } else if(measurement->unit != PG_MEASUREMENT_UNIT_KB) {
        return PG_ERR_MEASUREMENT_UNIT_CANT_CHANGE;
    }
    
    pg_mseq_t *seq = pg_create_measurement_sequence();
    seq->timestamp = pg_get_timestamp_usec();
    seq->value = pg_get_ram_usage();
    seq->tag = PG_STRDUP(tag);
    return pg_add_measurement_sequence(measurement, seq);
}