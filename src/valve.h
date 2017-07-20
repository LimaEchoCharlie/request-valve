
#ifndef _VALVE_H_
#define _VALVE_H_

#include <stdbool.h>

/**
 * @file
 * @brief Valve algorithm
 *
 */

/**
 * @brief Create a valve
 * @warning This must be called before any other value calls are made
 */
void valve_create( void );

/**
 * @brief Set the limits of the valve
 * @param[in] max_burst
 * @param[in] start_tokens
 * @param[in] rate_per_sec
 * @pre First create a valve 
 */
void valve_set( int max_burst, int start_tokens, float rate_per_sec);

/**
 * @brief Destroy the current valve
 */
void valve_destroy( void );

/**
 * @brief Test an IP address for membership in the current valve 
 * @param[in] ip_address An IP address
 * @return true if the valve contains the IP address, false otherwise
 * @pre First create a valve 
 */
bool valve_contains( char* ip_address );

/**
 * @brief Acquire a token for the given IP address
 * @param[in] ip_address An IP address
 * @return true if a token was acquired, false otherwise
 * @pre First create a valve 
 */
bool valve_acquire( char* ip_addr);


#endif
