#include <stdio.h>

extern void _alolang_8testPuts(void) { puts("AloLang Test Function"); }

extern void _alolang_12testPrintInt3inte(long long a) { printf("%lld\n", a); }
extern void _alolang_15testPrintDouble6doublee(double a) { printf("%lf\n", a); }
extern void _alolang_13testPrintBool4boole(int a)
{
    if (a) {
        printf("true\n");
    } else {
        printf("false\n");
    }
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
