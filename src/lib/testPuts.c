#include <stdio.h>

extern void string2char(int *data, long long length, char *dst);

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
    char buff[str.data.size * 4 + 1];
    string2char((int *)str.data.pointer.addr, str.data.size, buff);
    printf("%s\n", buff);
};

extern void _alolang_13testPrintBool4boole(int a)
{
    if (a) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

extern void _alolang_13testPrintChar4chare(int alochar)
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
