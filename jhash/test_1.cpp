#include <iostream>
#include "jhash.h"
#include <stdio.h>
#include <string.h>

using namespace std;

#define HASH_SIZE                   2048
class Test{
public:
    int m_data;
    Test(int data = 0):m_data(data){
    }
};
int main(void)
{
    Test obj1(1);
    Test obj2(2);
    unsigned int uHashKey = jhash(reinterpret_cast<u8*>(&obj1), sizeof(Test), 0xabcdef98);
    unsigned int i = uHashKey % (HASH_SIZE - 1);
    printf("%u, %u\n", uHashKey, i);

    unsigned int uHashKey1 = jhash(reinterpret_cast<u8*>(&obj2), sizeof(Test), 0xabcdef98);
    unsigned int i1 = uHashKey1 % (HASH_SIZE - 1);
    printf("%u, %u\n", uHashKey1, i1);
#if 0
    char s[] = "1234";
    unsigned int uHashKey = jhash((u8*)s, strlen(s) + 1, 0xabcdef98);
    unsigned int i = uHashKey % (HASH_SIZE - 1);
    printf("%u, %u\n", uHashKey, i);
    char s1[] = "1236";
    unsigned int uHashKey1 = jhash((u8*)s1, strlen(s1) + 1, 0xabcdef98);
    unsigned int i1 = uHashKey1 % (HASH_SIZE - 1);
    printf("%u, %u\n", uHashKey1, i1);
#endif
    return 0;
}
