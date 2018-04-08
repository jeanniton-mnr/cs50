
# This program test if a credit card number is valid
# Author: Jeanniton Monero
# email: jeanniton.mnr@gmail.com
# website: jeanniton.me




def main():
    card_number = None
    card_number_str = None
    card_len = None
    total = None

    # Get card number
    print("Number: ", end="")
    card_number = (int)(input())

    # Get string representation of card number
    card_number_str = str(card_number)
    # Number of digit of card
    card_len = len(card_number_str)
    # Initialize `total` to zero (0)
    total = 0

    # Multiply each second/other digit by two (2) and
    # add those products' digit together.
    # NB: Starting at the last second digit
    i = card_len - 2
    while i >= 0:
        digit = int(card_number_str[i])
        # Decrement `i` to two (2) step
        i -= 2

        # Multiply digit by two (2)
        prod = digit * 2

        # Add product to `total`
        rest = prod - 10
        if rest >= 0:
            total += rest
            total += 1
        else:
            total += prod

    # Let reset the variable `i`
    i = None

    # Now let's add the `total` of the digits that weren't multiplied by 2 to the `total`:
    i = card_len - 1
    while i >= 0:
        digit = int(card_number_str[i])
        total += digit
        # Decrement `i` to two (2) step
        i -= 2

    # Let reset the variable `i`
    i = None

    # Check to see if the CC number is valid and in the appropriate range
    if total % 10 == 0:
        # Check AMEX CC
        if (card_number >= 340000000000000 and card_number < 350000000000000) or (card_number >= 370000000000000 and card_number < 380000000000000):
            print("AMEX")
        # Check MASTERCARD CC
        elif card_number >= 5100000000000000 and card_number < 5600000000000000:
            print("MASTERCARD")
        # Check VISA CC
        elif (card_number >= 4000000000000 and card_number < 5000000000000) or (card_number >= 4000000000000000 and card_number < 5000000000000000):
            print("VISA")
        # No CC match: Print INVALID
        else:
            print("INVALID")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()