#ifndef __SNOWFLAKE__
#define __SNOWFLAKE__

#define SNOWFLAKE_EPOCH 1576080000000 //2019-12-12

#define SNOWFLAKE_TIME_BITS 41
#define SNOWFLAKE_REGIONID_BITS 4
#define SNOWFLAKE_WORKERID_BITS 10
#define SNOWFLAKE_SEQUENCE_BITS 8
typedef struct _snowflake_state  snowflake;
struct _snowflake_state {
    long long int time;
    long int seq_max;
    long int worker_id;
    long int region_id;
    long int seq;
    long int time_shift_bits;
    long int region_shift_bits;
    long int worker_shift_bits;
};

long long int snowflake_id(snowflake *);
int snowflake_init(int region_id, int worker_id, snowflake *);

#endif /* __SNOWFLAKE__ */