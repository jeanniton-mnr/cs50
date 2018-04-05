// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize factor infile outfile\n");
        return 1;
    }

    // remember filenames
    int factor = atoi(argv[1]);
    if(factor < 0 || factor > 100){
        fprintf(stderr, "Error: Factor must be a valid integer between ]0 - 100] .");
        return 1;
    }
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


    //                   =======                    //
    // This is where I will start altering copy.c
    //                   =======                   //

    int originalWidth = bi.biWidth;
    int originalHeight = bi.biHeight;
    bi.biWidth *= factor;
    bi.biHeight *= factor;

    // Calculate the padding for inptr
    int originalPadding = (4 - (originalWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // Calculate the padding for outptr
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = abs(bi.biHeight) * (bi.biWidth * sizeof(RGBTRIPLE) + padding);
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    for(int i=0; i < abs(originalHeight); i++){

        // Write scanline factor time(s)
        for(int j=0; j < factor; j++){
            // Write scanline
            for(int k=0; k < originalWidth; k++){
                RGBTRIPLE pixel;
                fread(&pixel, sizeof(RGBTRIPLE), 1, inptr);
                // Write pixel factor time(s)
                for(int l=0; l < factor; l++){
                    fwrite(&pixel, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // Add padding at the end of scanline for outptr
            for(int l=0; l < padding; l++){
                fputc(0x00, outptr);
            }

            // Return at the start of the scanline
            fseek(inptr, -(originalWidth * sizeof(RGBTRIPLE)), SEEK_CUR);

        }


        // Seek scanline with padding included for inptr
        fseek(inptr, originalWidth * sizeof(RGBTRIPLE) + originalPadding, SEEK_CUR);

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
