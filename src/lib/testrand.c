#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

extern long long _alolang_8testRand(void) { return rand(); }

extern long long _alolang_8testTime(void)
{
    struct timespec spec;
    clock_gettime(0, &spec);
    long long ns = spec.tv_sec * 1000000 + spec.tv_nsec;
    return ns;
}
