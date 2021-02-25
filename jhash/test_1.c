#include "jhash.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[] = "1234";
    unsigned int uHashKey = jhash((u8*)s, strlen(s) + 1, 0xabcdef98);
    printf("%u\n", uHashKey);
    return 0;
}
