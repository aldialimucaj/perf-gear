/** @brief Linked list to managed working measurements 
 * 
 * @file linked-list.h
 * @author Aldi Alimucaj
 *
 * @date March 10, 2015, 2:30 PM
 * 
 * Elements in this list are measurement that are currently
 * waiting for events.
 * 
 */

#ifndef LINKED_LIST_H
#define	LINKED_LIST_H

#include "queue.h"

#ifdef	__cplusplus
extern "C" {
#endif

    /** @brief Linked list element.
     */
    typedef struct pg_linked_list_item {
        pg_m_item_t *m;
        struct pg_linked_list_item *next;
    } pg_ll_item_t;

    pg_ll_item_t* pg_ll_first_item;


    /** @brief Create a new Linked List Item
     * 
     * @return new allocated linked list
     */
    pg_ll_item_t* pg_ll_create(void);

    /** @brief destroy Linked List Item.
     * 
     * This function doesn't destroy the payload.
     * You have to take care of the measurement.
     * 
     * @param item
     * @return 
     */
    pg_err_t pg_ll_destroy(pg_ll_item_t* item);

    /** @brief Add new item to the pg_ll_first_item List
     * 
     * @param item Item to add
     * @return 
     */
    pg_err_t pg_ll_add(pg_m_item_t *item);


    /** @brief Add new item to the specified List
     * 
     * @param item Item to add
     * @param list List to add it to
     * @return 
     */
    pg_err_t pg_ll_add_to(pg_m_item_t *item, pg_ll_item_t* list);

    /** @brief Get item from the list.
     * 
     * Does not remove the item from the list.
     * 
     * @param path
     * @return 
     */
    pg_m_item_t* pg_ll_get(const char *path);

    /** @brief Returns the last element of the list.
     * 
     * @return 
     */
    pg_ll_item_t* pg_ll_get_last(void);

    /** @brief Get the last item and remove it from the list.
     * 
     * @return 
     */
    pg_m_item_t* pg_ll_pop(void);

    /** @brief Get item matching path and remove it from the list.
     * 
     * @param path 
     * @return 
     */
    pg_m_item_t* pg_ll_pull(char *path);

    /** @brief Returns the size of the chain.
     * 
     * @return 
     */
    long pg_ll_get_size(void);


    /** @brief Remove all items form the list
     * 
     * @return 
     */
    pg_err_t pg_ll_clear(void);



#ifdef	__cplusplus
}
#endif

#endif	/* LINKED_LIST_H */

