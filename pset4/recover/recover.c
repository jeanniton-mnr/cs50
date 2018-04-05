#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE  512

int main(int argc, char *argv[])
{

  // ensure proper usage
  if(argc != 2)
  {
    fprintf(stderr, "Usage: ./recover rawdata.\n");
    return 1;
  }

  // check for valid file
  char *raw_file = argv[1];
  FILE *inptr = fopen(raw_file, "r");
  if(inptr == NULL)
  {
    fprintf(stderr, "Could not open file %s.\n", raw_file);
    return 2;
  }

  unsigned char *block = malloc(BLOCK_SIZE);
  int jpg_counter = 0;
  FILE *img_outptr;

  while(fread(block, BLOCK_SIZE, 1, inptr))
  {
    // test to see if start of file match the start of a jpg file
    if(block[0] == 0xFF && block[1] == 0xD8 && block[2] == 0xFF && (block[3] & 0xF0) == 0xE0)
    {
      // close previous jpg file
      if(jpg_counter > 0) fclose(img_outptr);

      // create filename
      char filename[7];
      sprintf(filename, "%03i.jpg", jpg_counter);

      // open new image file
      img_outptr = fopen(filename, "w");

      // check if jpg file is successfully created
      if(img_outptr == NULL)
      {
        fclose(inptr);
        free(block);
        fprintf(stderr, "Could not create output JPG %s", filename);
        return 3;
      }

      jpg_counter++;
    }

    // check to see if we are working on a jpg
    if(!jpg_counter) continue;

    // write jpg block into working file
    fwrite(block, BLOCK_SIZE, 1, img_outptr);
  }

  fclose(inptr);
  fclose(img_outptr);

  // free block memory
  free(block);

  return 0;
}