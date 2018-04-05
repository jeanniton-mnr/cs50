#include <stdio.h>

// This softwate test if the first four bits of `bits` is equal to 0xe or 1110

int main(void)
{

    int bits = 0xEF;
    int mask = 0xF0;

    int test = 0xE0;

    int result = bits & mask;

    if(result == test){
        printf("First four bits of 'bits' is equal to 0xE.\n");
    }else{
        printf("First four bits of 'bits' is different from 0xE.\n");
    }

}