/*
 * This program use box blur to a .bmp image.
 *
 * Completion time: 23 hrs
 * Author: Xiaolou Huang (Lor).
 * Version: 10/10/2018.
 *
 */
/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/*#include <math.h> #include <stdint.h> make sure the int size is 32 bits */

/*MACRO DEFINITIONS*/
#pragma warning(disable: 4996)
/* #pragma pack(push, 1) change alignment to 1 bytes, exact fit, no padding */

/*problem assumptions*/
#define BMP_HEADER_SIZE_BYTES 14
#define BMP_DIB_HEADER_SIZE_BYTES 40
#define MAXIMUM_IMAGE_SIZE 256

/*bmp compression methods*/
/*none:*/
#define BI_RGB 0

/*********************************************************************************************************/

/*DATA STRUCTURES*/
struct BMP_Header {
    char signature[2]; /* ID field */
    unsigned int size; /* Size of the BMP file */
    short reserved1; /* Application specific */
    short reserved2; /* Application specific */
    unsigned int offset_pixel_array; /* Offset where the pixel array (bitmap data) can be found */
};

struct DIB_Header {
    unsigned int size; /* Header size in bytes (4 bytes)*/
    int width; /* Width of image (4 bytes) */
    int height; /* Height of image (4 bytes) */
    unsigned short planes; /* Number of colour planes (2 bytes) */
    unsigned short bits; /* Bits per pixel (2 bytes) */
    unsigned int compression; /* Compression type (4 bytes) */
    unsigned int imageSize; /* Image size in bytes (4 bytes) */
    int xResolution; /* Horizontal resolution. Pixels per meter (4 bytes) */
    int yResolution; /* Vertical resolution. Pixels per meter (4 bytes) */
    unsigned int nColors; /* Number of colours (4 bytes) */
    unsigned int importantColors; /* Important colours (4 bytes) */
};

struct RGB_Value {
    unsigned char r; /* red value */
    unsigned char g; /* green value */
    unsigned char b; /* blue value */
};

/********************************************************************************************************/
/* Global variables */

/* forward declarations */
void boxBlur(FILE* file, struct DIB_Header dibHeader, struct BMP_Header bmpHeader);

/********************************************************************************************************/
int main(int argc, char* argv[]) {

    FILE* file;

    struct BMP_Header bmpHeader;
    struct DIB_Header dibHeader;

    file = fopen("test1wonderbread.bmp", "rb");

    /* read bmp header (14 bytes)*/
    fread(&bmpHeader.signature, (sizeof (char))*2, 1, file);
    fread(&bmpHeader.size, sizeof (unsigned int), 1, file);
    fread(&bmpHeader.reserved1, sizeof (short), 1, file);
    fread(&bmpHeader.reserved2, sizeof (short), 1, file);
    fread(&bmpHeader.offset_pixel_array, sizeof (unsigned int), 1, file);

    printf("signature: %c%c\n", bmpHeader.signature[0], bmpHeader.signature[1]);
    printf("size: %d\n", bmpHeader.size);
    printf("reserved1: %d\n", bmpHeader.reserved1);
    printf("reserved2: %d\n", bmpHeader.reserved2);
    printf("offset_pixel_array: %d\n\n", bmpHeader.offset_pixel_array);

    /* read dib header info (40 bytes) */
    fread(&dibHeader.size, sizeof (unsigned int), 1, file);
    fread(&dibHeader.width, sizeof (int), 1, file);
    fread(&dibHeader.height, sizeof (int), 1, file);
    fread(&dibHeader.planes, sizeof (unsigned short), 1, file);
    fread(&dibHeader.bits, sizeof (unsigned short), 1, file);
    fread(&dibHeader.compression, sizeof (unsigned int), 1, file);
    fread(&dibHeader.imageSize, sizeof (unsigned int), 1, file);
    fread(&dibHeader.xResolution, sizeof (int), 1, file);
    fread(&dibHeader.yResolution, sizeof (int), 1, file);
    fread(&dibHeader.nColors, sizeof (unsigned int), 1, file);
    fread(&dibHeader.importantColors, sizeof (unsigned int), 1, file);

    printf("size: %u\n", dibHeader.size);
    printf("width: %d\n", dibHeader.width);
    printf("height: %d\n", dibHeader.height);
    printf("planes: %d\n", dibHeader.planes);
    printf("bits: %d\n", dibHeader.bits);
    printf("compression: %u\n", dibHeader.compression);
    printf("imageSize: %u\n", dibHeader.imageSize);
    printf("xResolution: %d\n", dibHeader.xResolution);
    printf("yResolution: %d\n", dibHeader.yResolution);
    printf("nColors: %u\n", dibHeader.nColors);
    printf("importantColors: %u\n", dibHeader.importantColors);

    boxBlur(file, dibHeader, bmpHeader); /* do the box blur */

    fclose(file);
    return 0;
}

/*************************************************************************************************************/
/*************************************************************************************************************/
/*************************************************************************************************************/
/*MAIN PROGRAM CODE*/
/* Read the file and store RGB values to a 2D array, then call boxBlur method to blur the image, */

/* lastly, write the new RGB values to a new file. */
void boxBlur(FILE* file, struct DIB_Header dibHeader, struct BMP_Header bmpHeader) {

    /* variables declaration */
    int i, j, k;
    unsigned int sumR, sumG, sumB;
    int count; /* for counting how many neibors you have */
    int pixelCount; /* for pixel output  */
    int padR;
    int padW;
    FILE* fileW;
    FILE* fileR;
    struct BMP_Header bmpHeader1;
    struct DIB_Header dibHeader1;
    struct RGB_Value** pixel_array;

    /* initialize 2d pixel array*/
    pixel_array = (struct RGB_Value**) malloc(dibHeader.height * sizeof (struct RGB_Value*));
    for (i = 0; i < dibHeader.height; i++) {
        pixel_array[i] = (struct RGB_Value*) malloc(dibHeader.width * sizeof (struct RGB_Value));
    }

    fseek(file, bmpHeader.offset_pixel_array, SEEK_SET); /*offset ptr to where RGB value is stored */

    padR = (4 - (3 * dibHeader.width % 4)) % 4;
    for (i = 0; i < dibHeader.height; i++) {
        for (j = 0; j < dibHeader.width; j++) {
            fread(&pixel_array[i][j].b, sizeof (unsigned char), 1, file);
            fread(&pixel_array[i][j].g, sizeof (unsigned char), 1, file);
            fread(&pixel_array[i][j].r, sizeof (unsigned char), 1, file);
        }
        fseek(file, padR, SEEK_CUR);
    }

    /*pixelCount = 0;
    for (i = 0; i < dibHeader.height; i++) {
        for (j = 0; j < dibHeader.width; j++) {
            printf("--pixel %d ", pixelCount);
            printf("b: %u ", pixel_array[i][j].b);
            printf("g: %u ", pixel_array[i][j].g);
            printf("r: %u\n", pixel_array[i][j].r);
            pixelCount++;
        }
    }*/
    /********************************************************************************************************/
    /* Compute the needed RGB value for each pixel to blur the image. */

    sumR = 0;
    sumG = 0;
    sumB = 0;
    count = 0;

    /* for each pixel. */
    for (i = 0; i < dibHeader.width; i++) {
        for (j = 0; j < dibHeader.height; j++) {

            /* pixel itself */
            sumB += pixel_array[i][j].b;
            sumG += pixel_array[i][j].g;
            sumR += pixel_array[i][j].r;
            count++;

            /*printf("\nitself sumB: %u ", sumB);
            printf("itself sumG: %u ", sumG);
            printf("itself sumR: %u", sumR);
            printf("count: %d\n\n", count);*/

            /* pixel on down left, if any */
            if (i - 1 >= 0 && j + 1 < dibHeader.height) {
                sumB += pixel_array[i - 1][j + 1].b;
                sumG += pixel_array[i - 1][j + 1].g;
                sumR += pixel_array[i - 1][j + 1].r;
                count++;

                /*printf("dl sumB: %u ", sumB);
                printf("dl sumG: %u ", sumG);
                printf("dl sumR: %u ", sumR);
                printf("count: %d\n\n", count);*/
            }


            /* pixel on below, if any */
            if (j + 1 < dibHeader.height) {
                sumB += pixel_array[i][j + 1].b;
                sumG += pixel_array[i][j + 1].g;
                sumR += pixel_array[i][j + 1].r;
                count++;

                /*printf("b sumB: %u ", sumB);
                printf("b sumG: %u ", sumG);
                printf("b sumR: %u ", sumR);
                printf("count: %d\n\n", count);*/
            }


            /* pixel on down right, if any */
            if (i + 1 < dibHeader.width && j + 1 < dibHeader.height) {
                sumB += pixel_array[i + 1][j + 1].b;
                sumG += pixel_array[i + 1][j + 1].g;
                sumR += pixel_array[i + 1][j + 1].r;
                count++;

                /*printf("dr sumB: %u ", sumB);
                printf("dr sumG: %u ", sumG);
                printf("dr sumR: %u ", sumR);
                printf("count: %d\n\n", count);*/
            }


            /* pixel on left, if any */
            if (i - 1 >= 0) {
                sumB += pixel_array[i - 1][j].b;
                sumG += pixel_array[i - 1][j].g;
                sumR += pixel_array[i - 1][j].r;
                count++;

                /*printf("l sumB: %u ", sumB);
                printf("l sumG: %u ", sumG);
                printf("l sumR: %u ", sumR);
                printf("count: %d\n\n", count);*/
            }


            /* pixel on right, if any */
            if (i + 1 < dibHeader.width) {
                sumB += pixel_array[i + 1][j].b;
                sumG += pixel_array[i + 1][j].g;
                sumR += pixel_array[i + 1][j].r;
                count++;

                /*printf("r sumB: %u ", sumB);
                printf("r sumG: %u ", sumG);
                printf("r sumR: %u ", sumR);
                printf("count: %d\n\n", count);*/
            }


            /* pixel on top left, if any */
            if (i - 1 >= 0 && j - 1 >= 0) {
                sumB += pixel_array[i - 1][j - 1].b;
                sumG += pixel_array[i - 1][j - 1].g;
                sumR += pixel_array[i - 1][j - 1].r;
                count++;

                /*printf("tl sumB: %u ", sumB);
                printf("tl sumG: %u ", sumG);
                printf("tl sumR: %u ", sumR);
                printf("count: %d\n\n", count);*/
            }


            /* pixel on top, if any */
            if (j - 1 >= 0) {
                sumB += pixel_array[i][j - 1].b;
                sumG += pixel_array[i][j - 1].g;
                sumR += pixel_array[i][j - 1].r;
                count++;

                /*printf("t sumB: %u ", sumB);
                printf("t sumG: %u ", sumG);
                printf("t sumR: %u ", sumR);
                printf("count: %d\n\n", count);*/
            }


            /* pixel on top right, if any */
            if (i + 1 < dibHeader.width && j - 1 >= 0) {
                sumB += pixel_array[i + 1][j - 1].b;
                sumG += pixel_array[i + 1][j - 1].g;
                sumR += pixel_array[i + 1][j - 1].r;
                count++;

                /*printf("tr sumB: %u ", sumB);
                printf("tr sumG: %u ", sumG);
                printf("tr sumR: %u ", sumR);
                printf("count: %d\n\n", count);*/
            }


            /* assign new RGB values back to the pixel */
            pixel_array[i][j].b = (unsigned char) (sumB / count);
            /*printf("sumB/count %d\n\n", sumB/count);*/
            pixel_array[i][j].g = (unsigned char) (sumG / count);
            pixel_array[i][j].r = (unsigned char) (sumR / count);

            /*printf("ij B: %u ", pixel_array[i][j].b);
            printf("ij G: %u ", pixel_array[i][j].g);
            printf("ij R: %u ", pixel_array[i][j].r);
            printf("count: %d\n\n", count);
            printf("\n---------------------------------------------------------\n");*/

            sumR = 0;
            sumG = 0;
            sumB = 0;
            count = 0;

        }
    }
    /*pixelCount = 0;
    for (i = 0; i < dibHeader.height; i++) {
        for (j = 0; j < dibHeader.width; j++) {
            printf("--pixel %d ", pixelCount);
            printf("b: %u ", pixel_array[i][j].b);
            printf("g: %u ", pixel_array[i][j].g);
            printf("r: %u\n", pixel_array[i][j].r);
            pixelCount++;
        }
    }*/

    /******************************************************************************************************************/
    /*------------------------------------------------------------------------------------------*/
    fileW = fopen("test1wonderbreadblur.bmp", "wb");
    /*read bmp header (14 bytes)*/
    fwrite(&bmpHeader.signature, (sizeof (char))*2, 1, fileW);
    fwrite(&bmpHeader.size, sizeof (unsigned int), 1, fileW);
    fwrite(&bmpHeader.reserved1, sizeof (short), 1, fileW);
    fwrite(&bmpHeader.reserved2, sizeof (short), 1, fileW);
    fwrite(&bmpHeader.offset_pixel_array, 1, sizeof (unsigned int), fileW);

    /* read dib header info (40 bytes)*/
    fwrite(&dibHeader.size, sizeof (unsigned int), 1, fileW);
    fwrite(&dibHeader.width, sizeof (int), 1, fileW);
    fwrite(&dibHeader.height, sizeof (int), 1, fileW);
    fwrite(&dibHeader.planes, sizeof (unsigned short), 1, fileW);
    fwrite(&dibHeader.bits, sizeof (unsigned short), 1, fileW);
    fwrite(&dibHeader.compression, sizeof (unsigned int), 1, fileW);
    fwrite(&dibHeader.imageSize, sizeof (unsigned int), 1, fileW);
    fwrite(&dibHeader.xResolution, sizeof (int), 1, fileW);
    fwrite(&dibHeader.yResolution, sizeof (int), 1, fileW);
    fwrite(&dibHeader.nColors, sizeof (unsigned int), 1, fileW);
    fwrite(&dibHeader.importantColors, sizeof (unsigned int), 1, fileW);

    /* Write the data to a file. */
    /* fwrite(&bmpHeader, sizeof(struct ), 1, fileW);  /* write headers into file first */
    /* fwrite(&dibHeader, sizeof(unsigned char), 40, fileW); */
    padW = (4 - (3 * dibHeader.width % 4)) % 4;
    for (i = 0; i < dibHeader.height; i++) {
        for (j = 0; j < dibHeader.width; j++) {
            fwrite(&pixel_array[i][j].b, sizeof (unsigned char), 1, fileW);
            fwrite(&pixel_array[i][j].g, sizeof (unsigned char), 1, fileW);
            fwrite(&pixel_array[i][j].r, sizeof (unsigned char), 1, fileW);
        }
        fwrite(&pixel_array[i][j], padW, 1, fileW);
    }

    fclose(fileW);
    /*-------------------------------------------------------------------------------------*/
    fileR = fopen("test1wonderbreadblur.bmp", "rb");
    /* read bmp header (14 bytes) */
    fread(&bmpHeader1.signature, sizeof (char)*2, 1, fileW);
    fread(&bmpHeader1.size, sizeof (int), 1, fileW);
    fread(&bmpHeader1.reserved1, sizeof (short), 1, fileW);
    fread(&bmpHeader1.reserved2, sizeof (short), 1, fileW);
    fread(&bmpHeader1.offset_pixel_array, sizeof (int), 1, fileW);

    printf("\n\nfileW signature: %c%c\n", bmpHeader1.signature[0], bmpHeader1.signature[1]);
    printf("fileW size: %d\n", bmpHeader1.size);
    printf("fileW reserved1: %d\n", bmpHeader1.reserved1);
    printf("fileW reserved2: %d\n", bmpHeader1.reserved2);
    printf("fileW offset_pixel_array: %d\n\n", bmpHeader1.offset_pixel_array);

    /* read dib header info (40 bytes) */
    fread(&dibHeader1.size, sizeof (unsigned int), 1, fileW);
    fread(&dibHeader1.width, sizeof (int), 1, fileW);
    fread(&dibHeader1.height, sizeof (int), 1, fileW);
    fread(&dibHeader1.planes, sizeof (unsigned short), 1, fileW);
    fread(&dibHeader1.bits, sizeof (unsigned short), 1, fileW);
    fread(&dibHeader1.compression, sizeof (unsigned int), 1, fileW);
    fread(&dibHeader1.imageSize, sizeof (unsigned int), 1, fileW);
    fread(&dibHeader1.xResolution, sizeof (int), 1, fileW);
    fread(&dibHeader1.yResolution, sizeof (int), 1, fileW);
    fread(&dibHeader1.nColors, sizeof (unsigned int), 1, fileW);
    fread(&dibHeader1.importantColors, sizeof (unsigned int), 1, fileW);

    printf("fileW size: %u\n", dibHeader.size);
    printf("fileW width: %d\n", dibHeader.width);
    printf("fileW height: %d\n", dibHeader.height);
    printf("fileW planes: %d\n", dibHeader.planes);
    printf("fileW bits: %d\n", dibHeader.bits);
    printf("fileW compression: %u\n", dibHeader.compression);
    printf("fileW imageSize: %u\n", dibHeader.imageSize);
    printf("fileW xResolution: %d\n", dibHeader.xResolution);
    printf("fileW yResolution: %d\n", dibHeader.yResolution);
    printf("fileW nColors: %u\n", dibHeader.nColors);
    printf("fileW importantColors: %u\n", dibHeader.importantColors);

    fclose(fileW);
    /*------------------------------------------------------------------------------------------*/
}


