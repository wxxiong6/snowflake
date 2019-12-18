#include "snowflake.h"
#include <sys/time.h>
#include <stdio.h>

inline long long int timestamp_gen()
{
    struct  timeval    tv;
    gettimeofday(&tv, NULL);
    return (long long int)tv.tv_sec * 1000 + tv.tv_usec / 1000; 
}

long long int snowflake_id(snowflake *sf) {
    long long int millisecs = timestamp_gen();
    long long int id = 0LL;

    if (millisecs == sf->time)
    {
        sf->seq = (sf->seq + 1) & sf->seq_max;
        if (sf->seq == 0L) 
        {
            while (millisecs <= timestamp_gen())
            {
                millisecs = timestamp_gen();
            }
        }
    } else if (millisecs > sf->time) {
        sf->seq = 1L;
    } else {
        return 0L;
    }

    id = (millisecs-SNOWFLAKE_EPOCH << sf->time_shift_bits) 
            | (sf->region_id << sf->region_shift_bits) 
            | (sf->worker_id << sf->worker_shift_bits) 
            | (sf->seq); 


    sf->time = millisecs;

    return id;
}

int snowflake_init(int region_id, int worker_id, snowflake *sf) {
    int max_region_id = (1 << SNOWFLAKE_REGIONID_BITS) - 1;
    if(region_id < 0 || region_id > max_region_id){
        printf("Region ID must be in the range : 0-%d\n", max_region_id);
        return -1;
    }
    int max_worker_id = (1 << SNOWFLAKE_WORKERID_BITS) - 1;
    if(worker_id < 0 || worker_id > max_worker_id){
        printf("Worker ID must be in the range: 0-%d\n", max_worker_id);
        return -1;
    }
    
    sf->time_shift_bits   = SNOWFLAKE_REGIONID_BITS + SNOWFLAKE_WORKERID_BITS + SNOWFLAKE_SEQUENCE_BITS;
    sf->region_shift_bits = SNOWFLAKE_WORKERID_BITS + SNOWFLAKE_SEQUENCE_BITS;
    sf->worker_shift_bits = SNOWFLAKE_SEQUENCE_BITS;
    
    sf->worker_id    = worker_id;
    sf->region_id    = region_id;
    sf->seq_max      = (1L << SNOWFLAKE_SEQUENCE_BITS) - 1;
    sf->seq          = 0L;
    sf->time         = 0LL;
    return 1;
}