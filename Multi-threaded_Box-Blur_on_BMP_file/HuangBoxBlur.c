/*
 * This program use box blur to a .bmp image.
 *
 * Completion time: 27 hrs
 * Author: Xiaolou Huang (Lor).
 * Version: 10/10/2018.
 *
 * gcc -ansi -pedantic -Wall -pthread filename.c
 */
/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

/*MACRO DEFINITIONS*/
#pragma warning(disable: 4996)

/*problem assumptions*/
#define BMP_HEADER_SIZE_BYTES 14
#define BMP_DIB_HEADER_SIZE_BYTES 40
#define MAXIMUM_IMAGE_SIZE 256
#define THREAD_COUNT 25

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

struct Thread_Data {
    int tid;
    int hStart; /* the height to start with for this thread */
    int hEnd; /* the height to end with for this thread */
    int pixel_array_h; /* height of pixel_array */
    int pixel_array_w; /* width of pixel_array */
};

/********************************************************************************************************/
/* Global variables */
struct RGB_Value** pixel_array;

/* forward declarations */
void boxBlur(FILE* file, struct DIB_Header dibHeader, struct BMP_Header bmpHeader);
void* boxBlurThreading(void* arg);

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
/*MAIN PROGRAM CODE*/
/* Read the file and store RGB values to a 2D array, then call boxBlur method to blur the image, */

/* lastly, write the new RGB values to a new file. */
void boxBlur(FILE* file, struct DIB_Header dibHeader, struct BMP_Header bmpHeader) {

    /* variables declaration */
    int i, j, rc;
    /*-variables below for evenly distribute work to threads--------------------------------*/
    int pHeight;
    int pHeightAdd; /* how many time to add to each thread */
    int pHeightAddCount;
    int pHeightSum;
    /*--------------------------------------------------------------------------------*/
    pthread_t threadId[THREAD_COUNT];
    struct Thread_Data* thread_data;
    int padR; /* padding for input file */
    int padW; /* padding for output file */
    FILE* fileW;
    FILE* fileR;
    struct BMP_Header bmpHeader1; /* read the output file */
    struct DIB_Header dibHeader1;

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

    /*********************************************************************************************************/
    /*-----------------------------------------------------------------------------------------*/
    /* threading */
    /*pthread_attr_t attr; */
    thread_data = (struct Thread_Data*) malloc(THREAD_COUNT * sizeof (struct Thread_Data));

    /*----------------------------------------------------------------------------------------------*/
    /* calculate the even work for each thread */
    pHeightAdd = dibHeader.height % THREAD_COUNT;

    printf("\n--pHeightAdd remainder: %d\n", pHeightAdd);

    if (pHeightAdd == 0) {
        pHeight = dibHeader.height / THREAD_COUNT;
        for (i = 0; i < THREAD_COUNT; i++) {
            thread_data[i].tid = i;
            thread_data[i].pixel_array_h = dibHeader.height;
            thread_data[i].pixel_array_w = dibHeader.width;
            thread_data[i].hStart = i * pHeight;
            thread_data[i].hEnd = (i + 1) * pHeight - 1;
        }
    } else {
        pHeightAddCount = 0;
        pHeightSum = 0;
        pHeightAdd = dibHeader.height % THREAD_COUNT;
        pHeight = (dibHeader.height - pHeightAdd) / THREAD_COUNT;
        for (i = 0; i < THREAD_COUNT; i++) {
            thread_data[i].tid = i;
            thread_data[i].pixel_array_h = dibHeader.height;
            thread_data[i].pixel_array_w = dibHeader.width;
            if (pHeightAddCount < pHeightAdd) {
                thread_data[i].hStart = pHeightSum;
                thread_data[i].hEnd = pHeightSum + pHeight;
                pHeightSum += pHeight + 1;
                pHeightAddCount++;
            } else {
                thread_data[i].hStart = pHeightSum;
                thread_data[i].hEnd = pHeightSum + pHeight - 1;
                pHeightSum += pHeight;
            }
        }
    }
    /* testing code, can be deleted -------------------------------------------------------------*/
    for (i = 0; i < THREAD_COUNT; i++) {
        printf("thread %d: tid: %d, h: %d, w: %d, hStart: %d, hEnd: %d\n", i, thread_data[i].tid,
                thread_data[i].pixel_array_h, thread_data[i].pixel_array_w, thread_data[i].hStart, thread_data[i].hEnd);
    }
    /*-------------------------------------------------------------------------------------------*/
    /* create threads */
    for (i = 0; i < THREAD_COUNT; i++) {
        rc = pthread_create(&threadId[i], NULL, boxBlurThreading, (void*) &thread_data[i]);
        if (rc) {
            printf("Error creating thread %d rc: %d\n", i, rc);
            exit(-1);
        }
    }

    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threadId[i], NULL);
    }

    /******************************************************************************************************************/
    /*-write to output file----------------------------------------------------------------------------*/
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

    /* Write the pixel values to output file. */
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

    /*-read the output file, for testing, can be deleted--------------------------------------------------*/
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


    /* free memory and close files */
    for (i = 0; i < dibHeader.height; i++) {
        free(pixel_array[i]);
    }
    free(pixel_array);
    free(thread_data);
    fclose(fileW);
    /*------------------------------------------------------------------------------------------*/
}

/* Compute the needed RGB value for each pixel to blur the image. */
void* boxBlurThreading(void* thread_data) {
    unsigned int sumR, sumG, sumB;
    int i, j;
    int count; /* for counting how many neibors you have */

    struct Thread_Data* thread_data_i = thread_data;
    sumR = 0;
    sumG = 0;
    sumB = 0;
    count = 0;

    /* for each pixel. */
    for (i = 0; i < thread_data_i->pixel_array_w; i++) {
        for (j = thread_data_i->hStart; j <= thread_data_i->hEnd; j++) {

            /* pixel itself */
            sumB += pixel_array[i][j].b;
            sumG += pixel_array[i][j].g;
            sumR += pixel_array[i][j].r;
            count++;

            /* pixel on down left, if any */
            if (i - 1 >= 0 && j + 1 < thread_data_i->pixel_array_h) {
                sumB += pixel_array[i - 1][j + 1].b;
                sumG += pixel_array[i - 1][j + 1].g;
                sumR += pixel_array[i - 1][j + 1].r;
                count++;
            }

            /* pixel on below, if any */
            if (j + 1 < thread_data_i->pixel_array_h) {
                sumB += pixel_array[i][j + 1].b;
                sumG += pixel_array[i][j + 1].g;
                sumR += pixel_array[i][j + 1].r;
                count++;
            }

            /* pixel on down right, if any */
            if (i + 1 < thread_data_i->pixel_array_w && j + 1 < thread_data_i->pixel_array_h) {
                sumB += pixel_array[i + 1][j + 1].b;
                sumG += pixel_array[i + 1][j + 1].g;
                sumR += pixel_array[i + 1][j + 1].r;
                count++;
            }

            /* pixel on left, if any */
            if (i - 1 >= 0) {
                sumB += pixel_array[i - 1][j].b;
                sumG += pixel_array[i - 1][j].g;
                sumR += pixel_array[i - 1][j].r;
                count++;
            }

            /* pixel on right, if any */
            if (i + 1 < thread_data_i->pixel_array_w) {
                sumB += pixel_array[i + 1][j].b;
                sumG += pixel_array[i + 1][j].g;
                sumR += pixel_array[i + 1][j].r;
                count++;
            }

            /* pixel on top left, if any */
            if (i - 1 >= 0 && j - 1 >= 0) {
                sumB += pixel_array[i - 1][j - 1].b;
                sumG += pixel_array[i - 1][j - 1].g;
                sumR += pixel_array[i - 1][j - 1].r;
                count++;
            }

            /* pixel on top, if any */
            if (j - 1 >= 0) {
                sumB += pixel_array[i][j - 1].b;
                sumG += pixel_array[i][j - 1].g;
                sumR += pixel_array[i][j - 1].r;
                count++;
            }

            /* pixel on top right, if any */
            if (i + 1 < thread_data_i->pixel_array_w && j - 1 >= 0) {
                sumB += pixel_array[i + 1][j - 1].b;
                sumG += pixel_array[i + 1][j - 1].g;
                sumR += pixel_array[i + 1][j - 1].r;
                count++;
            }

            /* assign new RGB values back to the pixel */
            pixel_array[i][j].b = (unsigned char) (sumB / count);
            /*printf("sumB/count %d\n\n", sumB/count);*/
            pixel_array[i][j].g = (unsigned char) (sumG / count);
            pixel_array[i][j].r = (unsigned char) (sumR / count);

            sumR = 0;
            sumG = 0;
            sumB = 0;
            count = 0;
        }
    }

    pthread_exit(thread_data_i);
}
