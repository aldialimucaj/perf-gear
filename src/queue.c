// file: queue.c

#include "queue.h"

struct pg_queue* pg_init_queue(void) {
    if (pg_queue == NULL) {
        pg_queue = (struct pg_queue*) malloc(sizeof (struct pg_queue));
        if (pg_queue != NULL) {
            pg_queue->size = 0;
            pg_queue->head = NULL;
            pg_queue->tail = NULL;
        }
    }

    return pg_queue;
}

/* ========================================================================= */

pg_err_t pg_destroy_queue(void) {
    if (pg_queue != NULL) {
        if (pg_queue->size == 0) {
            free(pg_queue);
            pg_queue = NULL;
            return PG_NO_ERROR;
        } else {
            return PG_ERR_QUEUE_NOT_EMPTY;
        }
    }
    return PG_ERR_QUEUE_NOT_READY;
}

/* ========================================================================= */

pg_err_t pg_enqueue(pg_q_item_t *item) {
    /* checking */
    if (pg_queue == NULL) return PG_ERR_QUEUE_NOT_READY; // queue not ready 
    if (item == NULL) return PG_ERR_NO_Q_ITEM; // item is null, nothing to store

    /* creating new element */
    struct pg_queue_item *new_item = pg_create_queue_item();
    if (new_item != NULL) {
        /* if new item is ready, copy sub elements */
        if (item->measurement != NULL) {
            new_item->measurement = pg_create_measurement_item();
            if (new_item->measurement != NULL) {
                pg_copy_measurement_item(item->measurement, new_item->measurement);
            }
        }

        /* adding the element in the queue */
        if (pg_queue->size == 0 && pg_queue->head == NULL && pg_queue->tail == NULL) {
            /* this is the first element in the queue */
            pg_queue->head = new_item;
            pg_queue->tail = new_item;
        } else {
            /* add it in the tail */
            pg_queue->tail->next = new_item;
            pg_queue->tail = new_item;
        }
        pg_queue->size++;

    } else {
        return PG_ERR_COULD_NOT_CREATE; /* could not create new item */
    }
    return PG_NO_ERROR;
}

/* ========================================================================= */

pg_q_item_t* pg_dequeue(void) {
    if (!pg_queue) return NULL; // queue is not ready
    if (pg_queue->size == 0) return NULL; // queue is empty
    if (!pg_queue->head) return NULL; // error this should not happen 

    /* getting the first element */
    struct pg_queue_item *item = pg_queue->head;

    /* does it contain a next element? */
    if (item && item->next) {
        pg_queue->head = item->next;
    } else {
        pg_queue->head = NULL;
        pg_queue->tail = NULL;
    }

    /* decrease the queue's size */
    pg_queue->size--;
    return item;
}

/* ========================================================================= */

size_t pg_clear_queue(void) {
    if (!pg_queue) return -1; // queue is not ready 
    if (pg_queue->size == 0) return 0; // queue is empty

    /* element to be dequeued */
    struct pg_queue_item *current = NULL;

    size_t index = 0;
    while ((current = pg_dequeue()) != NULL) {
        pg_destroy_queue_item(current);
        index++;
    }
    return index;
}

/* ========================================================================= */

size_t pg_get_queue_size(void) {
    if (pg_queue != NULL) {
        return pg_queue->size;
    } else {
        return -1; // queue is not ready 
    }
}

/* ========================================================================= */

pg_q_item_t* pg_create_queue_item(void) {
    struct pg_queue_item *new_item = malloc(sizeof (struct pg_queue_item));
    new_item->measurement = NULL;
    new_item->next = NULL;
    return new_item;
}

/* ========================================================================= */

pg_err_t pg_destroy_queue_item(pg_q_item_t *item) {
    if (item) {
        /* does it contain a measurement? */
        if (item->measurement != NULL) {
            pg_destroy_measurement_item(item->measurement);
            item->measurement = NULL;
        }
        free(item);
        item = NULL;
        return PG_NO_ERROR;
    }

    return PG_ERR_NO_Q_ITEM; // cant destroy null
}

/* ========================================================================= */

pg_m_item_t* pg_create_measurement_item(void) {
    struct pg_measurement_item *new_item = malloc(sizeof (struct pg_measurement_item));
    new_item->path = NULL;
    new_item->sequence = NULL;
    new_item->hitValue = 0;
    new_item->type = PG_MEASUREMENT_TYPE_UNKNOWN;
    new_item->unit = PG_MEASUREMENT_UNIT_UNKNOWN;
    new_item->param = NULL;
    return new_item;
}

/* ========================================================================= */

pg_err_t pg_destroy_measurement_item(pg_m_item_t *item) {
    if (item) {
        /* does it contain a path? */
        if (item->path) {
            free(item->path);
        }
        /* does it contain a sequence? */
        if (item->sequence) {
            pg_clear_all_measurement_sequences(item);
        }
        /* does it contain dynamic parameters? */
        if (item->param) {
            pg_m_param_t *param = NULL;
            pg_m_param_t *cursor_param = item->param;
            while (cursor_param != NULL) {
                param = cursor_param;
                cursor_param = cursor_param->next;
                pg_destroy_measurement_param(param);
            }
        }

        free(item);
        item = NULL;
        return PG_NO_ERROR;
    }
    /* item was null */
    return PG_ERR_NO_MEASUREMENT;
}

/* ========================================================================= */

pg_err_t pg_copy_measurement_item(pg_m_item_t *src, pg_m_item_t *dst) {
    if (!src) return PG_ERR_NO_SOURCE; // nothing to copy 
    if (!dst) return PG_ERR_NO_DESTINATION; // nowhere to copy 
    memcpy(dst, src, sizeof (struct pg_measurement_item));
    /* sequences need to be copied, dump old reference */
    dst->sequence = NULL;
    dst->path = NULL;
    dst->param = NULL;
    dst->unit = src->unit;

    /* copy the path */
    if (src->path) {
        dst->path = malloc(sizeof (char) * (strlen(src->path) + 1));
        if (dst->path != NULL) {
            strncpy(dst->path, src->path, sizeof (char) * (strlen(src->path) + 1));
        }
    }

    /* copy the sequence */
    if (src->sequence) {
        pg_copy_measurement_sequences(src, dst);
    }

    /* copy dynamic parameters */
    if (src->param) {
        pg_copy_measurement_params(src, dst);
    }

    return PG_NO_ERROR;
}

/* ========================================================================= */

pg_mseq_t* pg_create_measurement_sequence(void) {
    struct pg_measurement_sequence *new_item = malloc(sizeof (struct pg_measurement_sequence));
    new_item->timestamp = 0;
    new_item->value = 0;
    new_item->tag = NULL;
    new_item->next = NULL;
    return new_item;
}

/* ========================================================================= */

pg_err_t pg_destroy_measurement_sequence(pg_mseq_t *item) {
    if (item) {
        if(item->tag) free(item->tag);
        free(item);
        item = NULL;
        return 0;
    }

    return PG_ERR_NO_MEASUREMENT_SEQ; // item was null 
}

/* ========================================================================= */

pg_err_t pg_add_measurement_sequence(pg_m_item_t *measurement, pg_mseq_t *seq) {
    if (!measurement) return PG_ERR_NO_MEASUREMENT; // No measurement
    if (!seq) return PG_ERR_NO_MEASUREMENT_SEQ; // No seq

    if (!measurement->sequence) {
        measurement->sequence = seq;
        return 0; // done here
    }

    pg_mseq_t *prev_seq = measurement->sequence;
    pg_mseq_t *current_seq = measurement->sequence;

    while ((current_seq = current_seq->next) != NULL) {
        prev_seq = current_seq;
    }

    /* we reached the last seq */
    prev_seq->next = seq;

    return PG_NO_ERROR;
}

/* ========================================================================= */

pg_err_t pg_copy_measurement_sequences(pg_m_item_t *src, pg_m_item_t *dst) {
    if (!src) return PG_ERR_NO_MEASUREMENT; // No source measurement
    if (!src->sequence) return PG_ERR_NO_MEASUREMENT_SEQ; // No seq
    if (!dst) return PG_ERR_NO_DESTINATION; // No destination measurement

    pg_mseq_t *src_current_seq = src->sequence;


    /* we are sure that at this point one seq item exists */
    do {
        pg_mseq_t *dest_seq = pg_create_measurement_sequence();
        memcpy(dest_seq, src_current_seq, sizeof (struct pg_measurement_sequence));
        /* remove the source's next */
        dest_seq->next = NULL;
        if(src_current_seq->tag) dest_seq->tag = PG_STRDUP(src_current_seq->tag);
        pg_add_measurement_sequence(dst, dest_seq);
        // TODO: check result
    } while ((src_current_seq = src_current_seq->next) != NULL);

    return PG_NO_ERROR;
}

/* ========================================================================= */

size_t pg_count_measurement_sequences(pg_m_item_t *measurement) {
    if (!measurement) return -1; // No measurement
    if (!measurement->sequence) return 0; // No sequences to destroy

    pg_mseq_t *current_seq = measurement->sequence;
    /* we are sure that at this point one seq item exists */
    size_t index = 1;
    while ((current_seq = current_seq->next) != NULL) {
        index++;
    }

    return index;
}

/* ========================================================================= */

size_t pg_clear_all_measurement_sequences(pg_m_item_t *measurement) {
    if (!measurement) return -1; // No measurement
    if (!measurement->sequence) return 0; // No sequences to destroy

    pg_mseq_t *prev_seq = measurement->sequence;
    pg_mseq_t *current_seq = measurement->sequence;
    /* we are sure that at this point one seq item exists */
    size_t index = 1;
    while ((current_seq = current_seq->next) != NULL) {
        pg_destroy_measurement_sequence(prev_seq);
        prev_seq = current_seq;
        index++;
    }
    /* destroy the last remaining seq */
    pg_destroy_measurement_sequence(prev_seq);
    measurement->sequence = NULL;

    return index;
}

/* ========================================================================= */

pg_m_param_t* pg_create_measurement_param(const char *key, pg_param_type_t type) {
    pg_m_param_t *param = malloc(sizeof (struct pg_measurement_param));
    if (param) {
        param->key = strdup(key);
        param->type = type;
        param->intValue = 0;
        param->doubleValue = 0;
        param->strValue = NULL;
        param->next = NULL;
    }

    return param;
}

/* ========================================================================= */

pg_err_t pg_destroy_measurement_param(pg_m_param_t *param) {
    pg_err_t err = PG_NO_ERROR;
    if (param) {
        free(param->key);
        switch (param->type) {
            case PG_PARAM_TYPE_STR:
                if (param->strValue) free(param->strValue);
                break;
            case PG_PARAM_TYPE_OBJ:
                if (param->objValue) err = pg_destroy_measurement_param(param->objValue);
                break;
            default:
                // nothing to do 
                break;
        }
        free(param);
    }

    return err;
}

/* ========================================================================= */

pg_err_t pg_param_copy_helper(pg_m_param_t *src, pg_m_param_t *dst) {
    if (!dst) return PG_ERR_BAD_ARG;
    pg_err_t err = PG_NO_ERROR;
    switch (src->type) {
        case PG_PARAM_TYPE_STR:
            dst->strValue = PG_STRDUP(src->strValue);
            break;
        case PG_PARAM_TYPE_INT:
            dst->intValue = src->intValue;
            break;
        case PG_PARAM_TYPE_DBL:
            dst->doubleValue = src->doubleValue;
            break;
        case PG_PARAM_TYPE_OBJ:
            if (src->objValue) {
                /* sub parameter */
                dst->objValue = pg_create_measurement_param(src->objValue->key, src->objValue->type);
                pg_param_copy_helper(src->objValue, dst->objValue);
            }
            break;
        case PG_PARAM_TYPE_UNKNOWN:
        default:
            err = PG_ERR_BAD_ARG;
            break;
    }

    /* sibling elements */
    if (src->next) {
        dst->next = pg_create_measurement_param(src->next->key, src->next->type);
        pg_param_copy_helper(src->next, dst->next);
    }

    return err;
}

/* ========================================================================= */

pg_err_t pg_copy_measurement_params(pg_m_item_t *src, pg_m_item_t *dst) {
    if (!src) return PG_ERR_NO_MEASUREMENT; // No source measurement
    if (!src->param) return PG_ERR_NO_MEASUREMENT_PARAM; // No seq
    if (!dst) return PG_ERR_NO_DESTINATION; // No destination measurement

    if (!dst->param) dst->param = pg_create_measurement_param(src->param->key, src->param->type);
    pg_param_copy_helper(src->param, dst->param);


    return PG_NO_ERROR;
}

/* ========================================================================= */

pg_err_t pg_msrt_add_param_str(pg_m_item_t *measurement, const char *key, const char *val) {
    if (!measurement) return PG_ERR_NO_MEASUREMENT; // No measurement
    pg_m_param_t *param = pg_create_measurement_param(key, PG_PARAM_TYPE_STR);
    param->strValue = strdup(val);

    if (!measurement->param) {
        measurement->param = param;
    } else {
        pg_m_param_t *last_param = measurement->param;
        pg_m_param_t *cursor_param = last_param;
        while ((cursor_param = cursor_param->next) != NULL) {
            last_param = cursor_param;
        }
        last_param->next = param;
    }

    return PG_NO_ERROR;
}