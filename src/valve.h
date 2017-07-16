
#ifndef _VALVE_H_
#define _VALVE_H_

#include <stdbool.h>

/**
 * @file
 * @brief Valve algorithm
 *
 */

void valve_create( void );

void valve_destroy( void );

bool valve_search( char* ip_address );

bool valve_acquire( char* ip_addr);

#endif
