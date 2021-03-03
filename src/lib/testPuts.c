#include <stdio.h>

extern void _alolang_8testPuts(void) { puts("AloLang Test Function"); }

extern void _alolang_12testPrintInt3int(long long a) { printf("%lld\n", a); }
extern void _alolang_15testPrintDouble6double(double a) { printf("%lf\n", a); }
extern void _alolang_13testPrintBool4bool(int a)
{
    if (a) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

extern int _alolang_10testGetInt()
{
    int a;
    scanf("%d", &a);
    return a;
}

extern double _alolang_13testGetDouble()
{
    double a;
    scanf("%f", &a);
    return a;   
}