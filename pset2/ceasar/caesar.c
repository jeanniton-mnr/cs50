#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argC, string argV[]){
    string plaintext;
    int key;
    int plaintext_len;

    if(argC >= 2){
        // Ask plainext from user
        plaintext = get_string("plaintext:  ");
        // Get plaintext length
        plaintext_len = strlen(plaintext);
        // Convert key to integer
        key = atoi(argV[1]);
        printf("ciphertext: ");
        // Encrypt plaintext
        for(int i=0; i < plaintext_len; i++){
            char encrypt_char;

            if(islower(plaintext[i]))
                encrypt_char = ((plaintext[i] + key - 97) % 26) + 97;

            else if(isupper(plaintext[i]))
                encrypt_char = ((plaintext[i] + key - 65) % 26) + 65;

            else
                encrypt_char = plaintext[i];

            printf("%c", encrypt_char);
        }
        printf("\n");
    }else{
        return 1;
    }

    return 0;
}