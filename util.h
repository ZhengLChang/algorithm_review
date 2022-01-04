#include <cstring>
#include <cstdint>
#include <sys/time.h>

uint64_t GetNowUsecs()
{
    timeval time_now;
    uint64_t t_now = 0;
    gettimeofday(&time_now, NULL);
    t_now = time_now.tv_sec * 1000000 + time_now.tv_usec;
    return t_now;
}


