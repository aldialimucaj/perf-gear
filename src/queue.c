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

int pg_enqueue(struct pg_queue_item *item) {
    /* checking */
    if (pg_queue == NULL) return 1; /* queue not ready */
    if (item == NULL) return 2; /* item is null, nothing to store */

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

struct pg_queue_item* pg_dequeue(void) {
    if (!pg_queue) return NULL; /* queue is not ready */
    if (pg_queue->size == 0) return NULL; /* queue is empty */
    if (!pg_queue->head) return NULL; /* error this should not happen */

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

int pg_clear_queue(void) {
    if (!pg_queue) return 0; /* queue is not ready */
    if (pg_queue->size == 0) return 0; /* queue is empty */

    /* element to be dequeued */
    struct pg_queue_item *current;

    long index = 0;
    while ((current = pg_dequeue()) != NULL) {
        pg_destroy_queue_item(current);
        index++;
    }
    return index;
}

struct pg_queue_item* pg_create_queue_item(void) {
    struct pg_queue_item *new_item = malloc(sizeof (struct pg_queue_item));
    new_item->measurement = NULL;
    new_item->next = NULL;
    return new_item;
}

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

    return 1; /* cant destroy null */
}

struct pg_measurement_item* pg_create_measurement_item(void) {
    struct pg_measurement_item *new_item = malloc(sizeof (struct pg_measurement_item));
    new_item->path = NULL;
    new_item->sequence = NULL;
    return new_item;
}

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

int pg_copy_measurement_item(struct pg_measurement_item *src, struct pg_measurement_item *dst) {
    if (!src) return 1; /* nothing to copy */
    if (!dst) return 2; /* nowhere to copy */
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

struct pg_measurement_sequence* pg_create_measurement_sequence(void) {
    struct pg_measurement_sequence *new_item = malloc(sizeof (struct pg_measurement_sequence));
    return new_item;
}

int pg_destroy_measurement_sequence(struct pg_measurement_sequence *item) {
    if (item) {
        free(item);
        item = NULL;
        return 0;
    }
    /* item was null */
    return 1;
}

long pg_get_queue_size(void) {
    if (pg_queue != NULL) {
        return pg_queue->size;
    } else {
        return -1; /* queue is not ready*/
    }
}
