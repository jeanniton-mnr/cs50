

#include <cs50.h>
#include <stdio.h>
#include <string.h>



char* number_to_string(long long number);
int to_int(char d);


int main(void) {

    long long card_number;
    char* card_number_str;
    int card_len;
    int sum;

    do{

        printf("Card Number: \n");
        card_number = get_long_long();

    }while(card_number < 0);

    // Convert card number to string
    card_number_str = number_to_string(card_number);
    // Number of digits of the card
    card_len = strlen(card_number_str);
    // Initialize sum to 0
    sum = 0;

    // Multiply each second/other digit by two (2) and
    // add those products' digit together.
    // NB: Starting to the last second digit.
    for(int i=card_len-2; i >= 0; i -= 2){

        int digit = to_int(card_number_str[i]);

        // Mutiply digit by two (2)
        int prod = digit * 2;

        // Add product to sum
        int rest = prod - 10;
        if(rest >= 0){
            sum += rest;
            sum++;
        }else{
            sum += prod;
        }

    }

    // Now let’s add the sum of the digits that weren’t multiplied by 2 to the sum:
    for(int i=card_len-1; i >= 0; i -= 2){
        sum += to_int(card_number_str[i]);
    }

    // check to see if the CC number is valid and in the appropriate range
    if ( sum % 10 == 0 )
    {
        if ( (card_number >= 340000000000000 && card_number < 350000000000000) || (card_number >= 370000000000000 && card_number < 380000000000000) ){
            printf("AMEX\n");
        }
        else if ( card_number >= 5100000000000000 && card_number < 5600000000000000 ) {
            printf("MASTERCARD\n");
        }

        else if ( (card_number >= 4000000000000 && card_number < 5000000000000) || (card_number >= 4000000000000000 && card_number < 5000000000000000) ) {
            printf("VISA\n");
        }
        else {
            printf("INVALID\n");
        }
    }else{
         printf("INVALID\n");
    }


    //printf("%i", sum);
    //printf("\n");

    return 0;
}


char* number_to_string(long long number) {
    char *string = malloc (256 * sizeof (char));
    sprintf(string, "%lld", number);

    return string;
}

int to_int(char d)
{
 char str[2];

 str[0] = d;
 str[1] = '\0';
 return (int) strtol(str, NULL, 10);
}