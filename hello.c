#include <cs50.h>
#include <stdio.h>


int main(void)
{
    string s = get_string("your name: \n");

    printf("Hello, %s\n", s);
}

