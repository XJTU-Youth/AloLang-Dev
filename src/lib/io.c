#include "types/alostring.h"
#include "ucs4support.h"
#include <stdio.h>

// print(int)
extern void _alolang_5print3inte(long long a) { printf("%lld\n", a); }

// print(double)
extern void _alolang_5print6doublee(double a) { printf("%lf\n", a); }

// print(string)
extern void _alolang_5print6stringe(struct alostring str)
{
    char buff[str.data.size * 4 + 1];
    string2char((int *)str.data.pointer.addr, str.data.size, buff);
    printf("%s\n", buff);
};

// print(bool)
extern void _alolang_5print4boole(int a)
{
    if (a) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

// print(char)
extern void _alolang_5print4chare(int alochar)
{
    char a[5];
    string2char(&alochar, 1, a);
    printf("%s\n", a);
}

extern long long _alolang_10testGetInte()
{
    long long a;
    scanf("%lld", &a);
    return a;
}

extern double _alolang_13testGetDoublee()
{
    double a;
    scanf("%lf", &a);
    return a;
}
