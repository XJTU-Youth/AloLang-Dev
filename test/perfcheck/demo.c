#include <stdio.h>

int main(void)
{
    long long int a = 1;
    long long int b = 1;
    long long int c;
    while (a < 4611686018427387903) {
        c = a + b;
        b = a;
        a = c;
    }
    printf("a = %lld\n", a);
    return 0;
}