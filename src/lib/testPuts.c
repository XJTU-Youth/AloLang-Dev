#include <stdio.h>

extern void _alolang_8testPuts(void) { puts("AloLang Test Function"); }

extern void _alolang_12testPrintInt3int(int a) { printf("%d\n", a); }

extern int _alolang_10testGetInt()
{
    int a;
    scanf("%d", &a);
    return a;
}
