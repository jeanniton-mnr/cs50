

# Print mario wall
# Author: Jeanniton Monero
# email: jeanniton.mnr@gmail.com
# website: jeanniton.me


def main():

    # The height of the pyramid
    height = -1

    # Get pyramid height. re-ask if given value isn't valid range
    while height < 0 or height > 23:
        print("Pyramid height: ")
        height = (int)(input())

    # Build the pyramid
    for i in range(height):
        # Print the spaces within this row
        for j in range(height-i-1):
            print(" ", end="")
        for k in range(i+2):
            print("#", end="")
        # Go to new row
        print("")


if __name__ == "__main__":
    main()