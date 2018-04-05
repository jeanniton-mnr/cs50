
#include <cs50.h>
#include <string.h>
#include <stdlib.h>


// Concatenate a string and a char
char* concatenate (char *str, char c)
{
    char temp[2];
    temp[0] = c;
    temp[1] = '\0';

    return concatenate(str, temp);
};

// Concatenate two strings
char* concatenate (char *str1, char *str2)
{
    return strcat(str1, str2);
};

// Crash the program
void crash (int errorCode, const char* msg)
{
    eprintf(msg);
    exit(errorCode);
};