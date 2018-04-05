
#include <stdio.h>
#include <cs50.h>

int main(void)
{
	// The height of the pyramid
	int height = 0;

	// Get pyramid height. re-ask if given value isn't valid range
	do {
		printf("Pyramid height: ");
		height = get_int();
	} while (height < 0 || height > 23);

	// Build the pyramid
	for(int i = 0; i < height; i++)
	{
		// Print the spaces within this row
        for(int j = 0; j < height-i-1; j++)
        {
            printf("%s", " ");
        }
        // Print the '#' within this row
		for(int k = 0; k < i+2; k++)
		{
			printf("#");
		}
		printf("\n");
	}
	return 0;
}