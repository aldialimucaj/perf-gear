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

int pg_destroy_queue(void) {
    if (pg_queue != NULL) {
        if (pg_queue->size == 0) {
            free(pg_queue);
            pg_queue = NULL;
            return 0;
        }
    }
    return 1;
}

/* ========================================================================= */

int pg_enqueue(struct pg_queue_item *item) {
    /* checking */
    if (pg_queue == NULL) return 1; // queue not ready 
    if (item == NULL) return 2; // item is null, nothing to store

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
        return 3; /* could not create new item */
    }
    return 0;
}

/* ========================================================================= */

struct pg_queue_item* pg_dequeue(void) {
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

int pg_clear_queue(void) {
    if (!pg_queue) return 0; // queue is not ready 
    if (pg_queue->size == 0) return 0; // queue is empty

    /* element to be dequeued */
    struct pg_queue_item *current;

    long index = 0;
    while ((current = pg_dequeue()) != NULL) {
        pg_destroy_queue_item(current);
        index++;
    }
    return index;
}

/* ========================================================================= */

long pg_get_queue_size(void) {
    if (pg_queue != NULL) {
        return pg_queue->size;
    } else {
        return -1; // queue is not ready 
    }
}

/* ========================================================================= */

struct pg_queue_item* pg_create_queue_item(void) {
    struct pg_queue_item *new_item = malloc(sizeof (struct pg_queue_item));
    new_item->measurement = NULL;
    new_item->next = NULL;
    return new_item;
}

/* ========================================================================= */

int pg_destroy_queue_item(struct pg_queue_item *item) {
    if (item) {
        /* does it contain a measurement? */
        if (item->measurement != NULL) {
            pg_destroy_measurement_item(item->measurement);
        }
        free(item);
        item = NULL;
        return 0;
    }

    return 1; // cant destroy null
}

/* ========================================================================= */

struct pg_measurement_item* pg_create_measurement_item(void) {
    struct pg_measurement_item *new_item = malloc(sizeof (struct pg_measurement_item));
    new_item->path = NULL;
    new_item->sequence = NULL;
    new_item->hitValue = 0;
    new_item->timeSpentValue = 0;
    new_item->type = PG_MEASUREMENT_TYPE_UNKNOWN;
    return new_item;
}

/* ========================================================================= */

int pg_destroy_measurement_item(struct pg_measurement_item *item) {
    if (item) {
        /* does it contain a path? */
        if (item->path) {
            free(item->path);
        }
        /* does it contain a sequence? */
        if (item->sequence) {
            pg_destroy_measurement_sequence(item->sequence);
        }
        free(item);
        item = NULL;
        return 0;
    }
    /* item was null */
    return 1;
}

/* ========================================================================= */

int pg_copy_measurement_item(struct pg_measurement_item *src, struct pg_measurement_item *dst) {
    if (!src) return 1; // nothing to copy 
    if (!dst) return 2; // nowhere to copy 
    memcpy(dst, src, sizeof (struct pg_measurement_item));

    /* copy the path */
    if (src->path) {
        dst->path = malloc(sizeof (char) * (strlen(src->path) + 1));
        if (dst->path != NULL) {
            strncpy(dst->path, src->path, sizeof (char) * (strlen(src->path) + 1));
        }
    }

    /* copy the sequence */
    if (src->sequence) {
        dst->sequence = malloc(sizeof (struct pg_measurement_sequence));
        if (dst->sequence != NULL) {
            memcpy(dst->sequence, src->sequence, sizeof (struct pg_measurement_sequence));
        }
    }

    return 0;
}

/* ========================================================================= */

struct pg_measurement_sequence* pg_create_measurement_sequence(void) {
    struct pg_measurement_sequence *new_item = malloc(sizeof (struct pg_measurement_sequence));
    new_item->next = NULL;
    return new_item;
}

/* ========================================================================= */

int pg_destroy_measurement_sequence(struct pg_measurement_sequence *item) {
    if (item) {
        free(item);
        item = NULL;
        return 0;
    }

    return 1; // item was null 
}

/* ========================================================================= */

int pg_add_measurement_sequence(struct pg_measurement_item *measurement, struct pg_measurement_sequence *seq) {
    if (!measurement) return -1; // No measurement
    if (!seq) return -2; // No seq

    if (!measurement->sequence) {
        measurement->sequence = seq;
        return 0; // done here
    }

    pg_mseq_t prev_seq = measurement->sequence;
    pg_mseq_t current_seq = measurement->sequence;

    while ((current_seq = current_seq->next) != NULL) {
        prev_seq = current_seq;
    }

    /* we reached the last seq */
    prev_seq->next = seq;

    return 0;
}

/* ========================================================================= */

long pg_count_measurement_sequences(struct pg_measurement_item *measurement) {
    if (!measurement) return -1; // No measurement
    if (!measurement->sequence) return 0; // No sequences to destroy

    pg_mseq_t current_seq = measurement->sequence;
    /* we are sure that at this point one seq item exists */
    long index = 1;
    while ((current_seq = current_seq->next) != NULL) {
        index++;
    }

    return index;
}

/* ========================================================================= */

long pg_clear_all_measurement_sequences(struct pg_measurement_item *measurement) {
    if (!measurement) return -1; // No measurement
    if (!measurement->sequence) return 0; // No sequences to destroy

    pg_mseq_t prev_seq = measurement->sequence;
    pg_mseq_t current_seq = measurement->sequence;
    /* we are sure that at this point one seq item exists */
    long index = 1;
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
