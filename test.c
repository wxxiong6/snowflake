#include "snowflake.c"

int main() 
{
    snowflake sf;
    snowflake_init(1, 1, &sf);
    int i;
    for(i = 0; i < 100; i++)
        printf("%lld \n", snowflake_id(&sf));
    return 0;
}