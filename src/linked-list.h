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

    typedef struct pg_linked_list_item* pg_ll_item_t;

    struct pg_linked_list_item {
        pg_m_item_t m;
        pg_ll_item_t next;
    };

    static pg_ll_item_t pg_ll_first_item = NULL;


    /** @brief Create a new Linked List Item
     * 
     * @return new allocated linked list
     */
    pg_ll_item_t pg_ll_create(void);

    /** @brief destroy Linked List Item.
     * 
     * This function doesn't destroy the payload.
     * You have to take care of the measurement.
     * 
     * @param item
     * @return 
     */
    pg_err_t pg_ll_destroy(pg_ll_item_t item);

    /** @brief Add new item to the pg_ll_first_item List
     * 
     * @param item item to add
     * @return 
     */
    pg_err_t pg_ll_add(pg_m_item_t item);


    /** @brief Add new item to the specified List
     * 
     * @param item item to add
     * @param list list to add it to
     * @return 
     */
    pg_err_t pg_ll_add_to(pg_m_item_t item, pg_ll_item_t list);

    /** @brief Get new item and remove from the list.
     * 
     * If the specified object has a next, it will be inserted in between.
     * 
     * @param path
     * @return 
     */
    pg_ll_item_t pg_ll_get(char *path);

    /** @brief Returns the last element of the list.
     * 
     * @return 
     */
    pg_ll_item_t pg_ll_get_last(void);


    /** @brief Remove all items form the list
     * 
     * @return 
     */
    pg_err_t pg_ll_clear(void);



#ifdef	__cplusplus
}
#endif

#endif	/* LINKED_LIST_H */

