#include "linked-list.h"

pg_ll_item_t* pg_ll_create(void) {
    pg_ll_item_t *item = malloc(sizeof (struct pg_linked_list_item));
    if (item) {
        item->m = NULL;
        item->next = NULL;
    }
    // write some error message
    return item;
}

/* ========================================================================= */

pg_err_t pg_ll_destroy(pg_ll_item_t *item) {
    free(item);
    item = NULL;
    return 0;
}

/* ========================================================================= */

pg_err_t pg_ll_add(pg_m_item_t *item) {
    if (!item) return PG_ERR_NO_MEASUREMENT; // no measurement;
    pg_ll_item_t *new_item = pg_ll_create();
    if (new_item) {
        new_item->m = item;
        if (!pg_ll_first_item) { // the first element
            pg_ll_first_item = new_item;
        } else {
            pg_ll_item_t *last = pg_ll_get_last();
            last->next = new_item;
        }
    }
    return PG_NO_ERROR;
}

/* ========================================================================= */

pg_m_item_t* pg_ll_get(char *path) {
    if (!path) return NULL; // no path;
    if (!pg_ll_first_item) return NULL; // no pg_ll_first_item;

    pg_ll_item_t *current = pg_ll_first_item;

    do {
        if (current->m && strcmp(path, current->m->path) == 0) {
            return current->m;
        }

        current = current->next;
    } while (current != NULL);

    return NULL;
}

/* ========================================================================= */

pg_m_item_t* pg_ll_pop(void) {
    if (!pg_ll_first_item) return NULL; // no pg_ll_first_item;

    pg_ll_item_t *pre = pg_ll_first_item;
    pg_ll_item_t *current = pg_ll_first_item;
    while (current->next != NULL) {
        pre = current;
        current = current->next;
    }

    pg_m_item_t *m = current->m;
    if (pre != current) {
        /* this is not the first and only element*/
        pg_err_t result = pg_ll_destroy(current);
        pre->next = NULL;
    } else {
        free(pg_ll_first_item);
        pg_ll_first_item = NULL;
    }

    return m;
}

/* ========================================================================= */

pg_m_item_t* pg_ll_pull(char *path) {
    if (!pg_ll_first_item) return NULL; // no pg_ll_first_item;
    if (!path) return NULL; // no path;


    pg_ll_item_t *pre = pg_ll_first_item;
    pg_ll_item_t *current = pg_ll_first_item;

    do {
        if (current->m && strcmp(path, current->m->path) == 0) {
            pg_m_item_t *m = current->m;
            if (current == pg_ll_first_item) {
                /* item has next*/
                if (pg_ll_first_item->next) {
                    pg_ll_first_item = pg_ll_first_item->next;
                    pg_ll_destroy(current);
                } else {
                    /* item has no next and can be freed */
                    free(pg_ll_first_item);
                    pg_ll_first_item = NULL;
                }
            } else {
                /* item has next*/
                if (current->next) {
                    pre->next = current->next;
                }
                pg_ll_destroy(current);
            }
            return m;
        }
        pre = current;
        current = current->next;
    } while (current != NULL);

    return NULL;
}

/* ========================================================================= */

pg_ll_item_t* pg_ll_get_last(void) {
    if (!pg_ll_first_item) return NULL;
    pg_ll_item_t *current = pg_ll_first_item;
    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}

/* ========================================================================= */

long pg_ll_get_size(void) {
    long result = 0;
    if (!pg_ll_first_item) return result;
    pg_ll_item_t *current = pg_ll_first_item;
    result++;
    while (current->next != NULL) {
        current = current->next;
        result++;
    }
    return result;
}


