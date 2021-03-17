#include <stdio.h>

char *string2char(int *data, long long length);

extern void _alolang_8testPuts(void) { puts("AloLang Test Function"); }

extern void _alolang_12testPrintInt3inte(long long a) { printf("%lld\n", a); }
extern void _alolang_15testPrintDouble6doublee(double a) { printf("%lf\n", a); }
struct aloptr {
    long long addr;
};
struct aloarray_char {
    struct aloptr pointer;
    long long     size;
};
struct alostring {
    struct aloarray_char data;
};
extern void _alolang_15testPrintString6stringe(struct alostring str)
{
    char *rstr = string2char((int *)str.data.pointer.addr, str.data.size);
    printf("%s\n", rstr);
};

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
