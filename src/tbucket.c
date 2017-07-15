
#include <time.h>

#include "tbucket.h"

 
static long current_time( void ){
    return (long) time(NULL);
}

static void top_up_bucket( tbucket_t* bucket ){
    long now = current_time();
    if( bucket->tokens < bucket->capacity ){
        int new_total = bucket->tokens + 
            (now - bucket->last_fill) * bucket->rate_per_sec;
        bucket->tokens = new_total > bucket->capacity ? 
                            bucket->capacity : new_total;
    }
    bucket->last_fill = now;
}

void tbucket_init( tbucket_t* bucket, int capacity, int start_tokens, int rate_per_sec ){
    bucket->capacity = capacity;
    bucket->tokens = start_tokens;
    bucket->rate_per_sec = rate_per_sec;
    bucket->last_fill = current_time();
}

int tbucket_available_tokens( tbucket_t* bucket ){
    top_up_bucket( bucket );
    return bucket->tokens;
}

/*
bool tbucket_acquire( tbucket_t* bucket, int tokens){
    top_up_bucket( bucket );
    if( tokens > bucket->tokens )
        return false;

    bucket->tokens -= tokens;
    return true;
}
 */
