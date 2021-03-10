#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
extern long long _alolang_8testRand(void) { return rand(); }

int64_t currentTimeMillis()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    int64_t s1 = (int64_t)(time.tv_sec) * 1000;
    int64_t s2 = (time.tv_usec / 1000);
    return s1 + s2;
}

extern long long _alolang_8testTime(void) { return currentTimeMillis(); }
