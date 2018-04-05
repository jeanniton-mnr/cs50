# Questions

## What's `stdint.h`?

`stdint.h` is a header file that allow to use `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` so we can declade variable or data type with specific width.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

`uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` allow you to declade variable or data type of a specific size.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

Respectively:
 A 'BYTE' is 1 byte.
 A 'DWORD' is 4 bytes.
 A 'LONG' is 4 bytes.
 A 'WORD' is 2 bytes.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The first two by in ASCII are "BM". It's there to ensere to identify BMP file and to confirm that it is not damaged.

## What's the difference between `bfSize` and `biSize`?

`bfSize` is the to the size of the bitmap file : 54 + rgbtripples.
'biSize' is the size of the image RGBTRIPPLE value per pixel for the image pixels.

## What does it mean if `biHeight` is negative?

If `biHeight` is negative, the bitmap is a top-down DIB and its origin is the upper-left corner

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

The field in `BITMAPINFOHEADER` that specifies the BMP's color depth is: biBitCount.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

`fopen` might return `NULL` in case it cannot create the file on the disk. The prob might relate to avaible disk space left, write permission, ...

## Why is the third argument to `fread` always `1` in our code?

It's because we are always reading 1 RGB tripple at a time.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

The value should be 1. 4 - 3 = 1.

## What does `fseek` do?

`fseek` move the current writting/reading position of the 'cursor'.

## What is `SEEK_CUR`?

This is an integer constant which, when used as the whence argument to the fseek or fseeko function, specifies that the offset provided is relative to the current file position