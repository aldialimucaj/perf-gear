/** 
 * @file collector.h
 * @author Aldi Alimucaj
 *
 * @date March 8, 2015, 11:29 AM
 * 
 * @brief The collector manages the life cycle of measurements.
 * 
 * It offers functions to create a new measurement, update, 
 * publish and destroy it.
 */

#ifndef COLLECTOR_H
#define	COLLECTOR_H


#include "pg-utils.h"
#include "queue.h"

#ifdef	__cplusplus
extern "C" {
#endif



    /** @brief Create a new measurement.
     * 
     * The new event should have as initial values a unique path to
     * distinguish it from other events. If a new path is identical to 
     * one that is active then the measurement will be refused. 
     * <i>Resources passed to this function are duplicated. Make
     * sure to release them because the destroy function wont.</i> 
     * 
     * @param path example "calc/fin/interest_rate"
     * @param type of measurement @ref pg_mtype_t
     * @sa pg_mtype_t
     * @return measurement_item or NULL
     */
    pg_m_item_t* pg_start_collecting(char *path, pg_mtype_t type);


    /** @brief Stop collecting and publish the measurement.
     * 
     * This also cleans up the measurement.
     * 
     * @param measurement
     * @return 0 = OK
     */
    pg_err_t pg_stop_collecting(pg_m_item_t *measurement);


    /** @brief Publish measurement for consumption
     * 
     * @param measurement
     * @return 
     */
    pg_err_t pg_publish_measurement(pg_m_item_t *measurement);


    /** @brief Increases the hit counter for a hit measurement.
     * 
     * If the measurement is not a hit counter then an error is returned.
     * 
     * @param measurement
     * @return 0 = OK
     */
    pg_err_t pg_increase_hit(pg_m_item_t *measurement);
    
    
    /** @brief Save the timestamp into the sequence.
     * 
     * This enables perf-gear to track the frequency of hits
     * for this object. Useful to build cycle graphs such as
     * MHz, FPS etc.
     * 
     * @param measurement
     * @return 
     */
    pg_err_t pg_save_timestamp(pg_m_item_t *measurement);


#ifdef	__cplusplus
}
#endif

#endif	/* COLLECTOR_H */

