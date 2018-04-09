
# A program that encrypts messages using Caesar’s cipher, per the below.
# See CS50 doc for more information
#
# Author: Jeanniton Monero
# email: jeanniton.mnr@gmail.com
# website: jeanniton.me

import sys


def main():

    paintext = ""
    key = int(sys.argv[1])
    plaintext_len = None


    if key >= 0:
        # Get plaintext from user
        plaintext = input("Plaintext: ")
        # Save plaintext length
        plaintext_len = len(plaintext)

        # Encrypt plaintext
        print("ciphertext: ", end="")
        for i in range(plaintext_len):
            # Get the ASCII number of a character
            char = plaintext[i]
            char_index = ord(char)
            encrypt_char = None
            if char.islower():
                # ord('a') = 97
                encrypt_char = ((char_index + key - 97) % 26) + 97
            elif char.isupper():
                # ord('A') = 65
                encrypt_char = ((char_index + key -65) %26) + 65
            else:
                encrypt_char = char_index
            # Print the character given by an ASCII number
            print(chr(encrypt_char), end="")
        # Print new line
        print("")

        return 0
    else:
        return 1



if __name__ == "__main__":
    main()