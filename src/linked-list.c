#include "linked-list.h"

pg_ll_item_t pg_ll_create(void) {
    pg_ll_item_t item = malloc(sizeof (struct pg_linked_list_item));
    if (item) {
        item->m = NULL;
        item->next = NULL;
    }
    // write some error message
    return item;
}

pg_err_t pg_ll_destroy(pg_ll_item_t item) {
    free(item);
    item = NULL;
    return 0;
}

pg_err_t pg_ll_add(pg_m_item_t item) {
    if (!item) return 1; // no measurement;
    pg_ll_item_t new_item = pg_ll_create();
    if (new_item) {
        new_item->m = item;
        if (!pg_ll_first_item) { // the first element
            pg_ll_first_item = new_item;
        } else {
            pg_ll_item_t last = pg_ll_get_last();
            last->next = new_item;
        }
    }
}

pg_ll_item_t pg_ll_get_last(void) {
    if (!pg_ll_first_item) return NULL;
    pg_ll_item_t current = pg_ll_first_item;
    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}

