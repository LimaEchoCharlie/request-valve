
#ifndef _TBUCKET_H_
#define _TBUCKET_H_

#include <stdbool.h>

typedef struct tbucket_s tbucket_t;

void tbucket_init( tbucket_t* bucket, int capacity, int start_tokens, int rate_per_sec );

int tbucket_available_tokens( tbucket_t* bucket );

bool tbucket_acquire( tbucket_t* bucket, int tokens);

struct tbucket_s{
    int capacity;
    int tokens;
    int rate_per_sec;
    long last_fill;
};

#endif
