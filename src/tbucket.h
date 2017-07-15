
#ifndef _TBUCKET_H_
#define _TBUCKET_H_

#include <stdbool.h>

/**
 * @file
 * @brief Token bucket algorithm
 *
 */

typedef struct tbucket_s tbucket_t;

/**
 * @brief Initialises a bucket with a fixed rate of flow R with bursts <= N
 * @param[in] bucket The token bucket
 * @param[in] capacity The maximum capacity of the bucket (max burst size N)
 * @param[in] start_tokens The number of tokens in the bucket at initialisation
 * @param[in] rate_per_sec The rate at which the bucket files (rate of flow R)
 */
void tbucket_init( tbucket_t* bucket, int capacity, int start_tokens, int rate_per_sec );

/**
 * @brief Count the number of tokens that are currently available in a given bucket
 * @param[in] bucket The token bucket
 * return Number of free tokens
 */
int tbucket_available_tokens( tbucket_t* bucket );

/**
 * @brief Acquires the given number of tokens from a given bucket
 * @param[in] bucket The token bucket
 * @param[in] tokens The number of permits to acquire
 * return true if the tokens were acquired, false otherwise
 */
bool tbucket_acquire( tbucket_t* bucket, int tokens);

struct tbucket_s{
    int capacity;       /**<Max capacity of bucket*/
    int tokens;         /**<Numner of tokens currently in bucket*/
    int rate_per_sec;   /**<Rate at which the bucket fills up*/
    long last_fill;     /**<Time when the bucket was last filled*/
};

#endif
