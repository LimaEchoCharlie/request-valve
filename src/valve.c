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

static bool valve_is_free = true;
static tbucket_t data_ptr[TABLE_SIZE];
static int ip_count_g = 0; 
static int max_burst_g = 100; 
static int start_tokens_g = 20;
static float rate_per_sec_g = 5.0;

void valve_create( void ){
    if( valve_is_free ){
        hcreate( TABLE_SIZE );
        valve_is_free = false;
    }
}

void valve_set( int max_burst, int start_tokens, float rate_per_sec){
    max_burst_g = max_burst; 
    start_tokens_g = start_tokens;
    rate_per_sec_g = rate_per_sec;
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

bool valve_contains( char* ip_address ){
    return find( ip_address ) != NULL;
}

bool valve_acquire( char* ip_address){
    ENTRY* entry_p = find( ip_address );
    if( entry_p == NULL ){
        ENTRY new_entry;
        
        // this looks like a memory leak but it isn't, keys are freed by hdestroy
        char * key = malloc(strlen( ip_address ) + 1 ); 
        strcpy( key, ip_address );
        tbucket_init( data_ptr+ip_count_g, max_burst_g, start_tokens_g, rate_per_sec_g);

        new_entry.key = key;
        new_entry.data = data_ptr+ip_count_g;
        ip_count_g++;

        entry_p = hsearch( new_entry, ENTER);
        return entry_p != NULL && tbucket_acquire( entry_p->data, 1);
        }

    tbucket_t* bucket = (tbucket_t* )entry_p->data;
    return tbucket_acquire( bucket, 1 );
}
