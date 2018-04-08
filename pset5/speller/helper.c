
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Crash the program
void crash (int errorCode)
{
    printf("Program exits because of an expected error.\n");
    printf("Error code: %i.\n", errorCode);
    exit(errorCode);
};

// Convert a string to lower case only
char* strLower(char *str)
{
    int length = strlen(str);
    for(int i = 0; i < length; i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}