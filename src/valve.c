#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <printf.h>
#include <string.h>
#include <search.h>

#include "valve.h"
#include "tbucket.h"

#define TABLE_SIZE 500
#define MAX_KEY_LEN 45     //maximum IPv6 string length is 45

static bool valve_is_free = true;
static char* key_ptr;
static tbucket_t* data_ptr;

void valve_create( void ){
    if( valve_is_free ){
        key_ptr = malloc(TABLE_SIZE * MAX_KEY_LEN);
        data_ptr = malloc(TABLE_SIZE * sizeof(tbucket_t));
        hcreate( TABLE_SIZE );
        valve_is_free = false;
    }
}

void valve_destroy( void ){
    if( !valve_is_free ){
        hdestroy();
        valve_is_free = true;
    }
}

static ENTRY* find( char* ip_address ){
    ENTRY entry, *found_entry_p;
    entry.key = ip_address;
    found_entry_p = hsearch( entry, FIND);
    return found_entry_p;
}

bool valve_search( char* ip_address ){
    return find( ip_address ) != NULL;
}

bool valve_acquire( char* ip_address){
    ENTRY* entry_p = find( ip_address );
    if( entry_p == NULL ){
        ENTRY new_entry;
        
        strcpy( key_ptr, ip_address );
        tbucket_init( data_ptr, 0, 0, 0);

        new_entry.key = key_ptr;
        new_entry.data = data_ptr;

        key_ptr += strlen( ip_address ) + 1;
        data_ptr++;

        entry_p = hsearch( new_entry, ENTER);
        return entry_p != NULL;
        }
    //todo add token acquire
    return false;
}
