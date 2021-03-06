#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

typedef struct tagBITMAPFILEHEADER {
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

void printFileHeader(BITMAPFILEHEADER bitmapFileHeader){
    printf("BITMAPFILEHEADER\n");
    printf("\tbfType: 0x%x\n", bitmapFileHeader.bfType);
    printf("\tbfSize: %d\n", bitmapFileHeader.bfSize);
    printf("\tbfReserved1: 0x%x\n", bitmapFileHeader.bfReserved1);
    printf("\tbfReserved2: 0x%x\n", bitmapFileHeader.bfReserved2);
    printf("\tbfOffBits: %d\n", bitmapFileHeader.bfOffBits);
}

void printInfoHeader(BITMAPINFOHEADER bitmapInfoHeader){
    printf("BITMAPINFOHEADER\n");
    printf("\tbiSize: %d\n", bitmapInfoHeader.biSize);
    printf("\tbiWidth: %d\n", bitmapInfoHeader.biWidth);
    printf("\tbiHeight: %d\n", bitmapInfoHeader.biHeight);
    printf("\tbiPlanes: %d\n", bitmapInfoHeader.biPlanes);
    printf("\tbiBitCount: %d\n", bitmapInfoHeader.biBitCount);
    printf("\tbiCompression: %d\n", bitmapInfoHeader.biCompression);
    printf("\tbiSizeImage: %d\n", bitmapInfoHeader.biSizeImage);
    printf("\tbiXPelsPerMeter: %d\n", bitmapInfoHeader.biXPelsPerMeter);
    printf("\tbiYPelsPerMeter: %d\n", bitmapInfoHeader.biYPelsPerMeter);
    printf("\tbiClrUsed: %d\n", bitmapInfoHeader.biClrUsed);
    printf("\tbiClrImportant: %d\n", bitmapInfoHeader.biClrImportant);
}

typedef struct Pixel{
    unsigned char b;
    unsigned char g;
    unsigned char r;
} PIXEL;

void printHist(char* colour, int* arr, int pxcount){
    printf("%s:\n", colour);
    int i = 0;
    float tmp = 100*(float)arr[i]/pxcount;
    printf("\t0-15: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("\t16-31: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("\t32-47: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("\t48-63: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("\t64-79: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("\t80-95: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("\t96-111: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("\t112-127: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("\t128-143: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("\t144-159: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("\t160-175: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("\t176-191: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("\t192-207: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("\t208-223: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("\t224-239: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("\t240-255: %.2f%%\n", tmp);
}

int main(int argc, char* argv[]){
    BITMAPFILEHEADER bitmapFileHeader; //bitmap file header
    BITMAPINFOHEADER bitmapInfoHeader; //bitmap info header

    // Open the file for Reading and validate it
    FILE *bmpfile;
    if (( bmpfile = fopen (argv[1], "rb")) == NULL) {
        fprintf (stderr, "error: file open failed '%s'\n", argv[1]);
        perror ("fopen");
        return 1;
    }

    // Open the file for Writing and validate it
    FILE *out;
    bool outopen = true;
    if (( out = fopen (argv[2], "wb")) == NULL) {
        printf("error: failed to open output file ('%s')\n", argv[2]);
        outopen = false;
    }

    // Copy the header to Output
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, bmpfile);
    fwrite(header, sizeof(unsigned char), 54, out);
    fseek(bmpfile, 0, SEEK_SET);

    // Read the bitmap File header
    fread(&bitmapFileHeader.bfType, 2, 1, bmpfile);
    fread(&bitmapFileHeader.bfSize, 4, 1, bmpfile);
    fread(&bitmapFileHeader.bfReserved1, 2, 1, bmpfile);
    fread(&bitmapFileHeader.bfReserved2, 2, 1, bmpfile);
    fread(&bitmapFileHeader.bfOffBits, 4, 1, bmpfile);

    // Read the bitmap Info header
    fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, bmpfile);

    // Print header information
    printFileHeader(bitmapFileHeader);
    printInfoHeader(bitmapInfoHeader);

    if (bitmapInfoHeader.biBitCount!=24 || bitmapInfoHeader.biCompression!=0){
        printf("Histogram calculation is unsupported.\n");
        fclose(bmpfile);
        if (outopen == true){
            fclose(out);
        }
        return 0;
    }

    PIXEL im[bitmapInfoHeader.biHeight][bitmapInfoHeader.biWidth];
    PIXEL gray;
    
    int pxcount = 0;
    int red[16] = {0};
    int green[16] = {0};
    int blue[16] = {0};
    int i, j;
    for (i = 0; i <= bitmapInfoHeader.biHeight; i++) {
        for (j = 0; j < bitmapInfoHeader.biWidth; j++) {
            fread(&im[i][j], sizeof(unsigned char), sizeof(PIXEL), bmpfile);
            pxcount++;

            // Calculate gray pixel value and write it to the file
            gray.r=im[i][j].r * 1/3 + im[i][j].g * 1/3 + im[i][j].b * 1/3;
            gray.g=im[i][j].r * 1/3 + im[i][j].g * 1/3 + im[i][j].b * 1/3;
            gray.b=im[i][j].r * 1/3 + im[i][j].g * 1/3 + im[i][j].b * 1/3;
            fwrite(&gray, sizeof(unsigned char), sizeof(PIXEL), out);

            //Blue
            if (im[i][j].b<16){
                blue[0]++;
            }
            else if (im[i][j].b>=16 && im[i][j].b<32){
                blue[1]++;
            }
            else if (im[i][j].b>=32 && im[i][j].b<48){
                blue[2]++;
            }
            else if (im[i][j].b>=48 && im[i][j].b<64){
                blue[3]++;
            }
            else if (im[i][j].b>=64 && im[i][j].b<80){
                blue[4]++;
            }
            else if (im[i][j].b>=80 && im[i][j].b<96){
                blue[5]++;
            }
            else if (im[i][j].b>=96 && im[i][j].b<112){
                blue[6]++;
            }
            else if (im[i][j].b>=112 && im[i][j].b<128){
                blue[7]++;
            }
            else if (im[i][j].b>=128 && im[i][j].b<144){
                blue[8]++;
            }
            else if (im[i][j].b>=144 && im[i][j].b<160){
                blue[9]++;
            }
            else if (im[i][j].b>=160 && im[i][j].b<176){
                blue[10]++;
            }
            else if (im[i][j].b>=176 && im[i][j].b<192){
                blue[11]++;
            }
            else if (im[i][j].b>=192 && im[i][j].b<208){
                blue[12]++;
            }
            else if (im[i][j].b>=208 && im[i][j].b<224){
                blue[13]++;
            }
            else if (im[i][j].b>=224 && im[i][j].b<240){
                blue[14]++;
            }
            else if (im[i][j].b>=240 && im[i][j].b<256){
                blue[15]++;
            }
            //Green
            if (im[i][j].g<16){
                green[0]++;
            }
            else if (im[i][j].g>=16 && im[i][j].g<32){
                green[1]++;
            }
            else if (im[i][j].g>=32 && im[i][j].g<48){
                green[2]++;
            }
            else if (im[i][j].g>=48 && im[i][j].g<64){
                green[3]++;
            }
            else if (im[i][j].g>=64 && im[i][j].g<80){
                green[4]++;
            }
            else if (im[i][j].g>=80 && im[i][j].g<96){
                green[5]++;
            }
            else if (im[i][j].g>=96 && im[i][j].g<112){
                green[6]++;
            }
            else if (im[i][j].g>=112 && im[i][j].g<128){
                green[7]++;
            }
            else if (im[i][j].g>=128 && im[i][j].g<144){
                green[8]++;
            }
            else if (im[i][j].g>=144 && im[i][j].g<160){
                green[9]++;
            }
            else if (im[i][j].g>=160 && im[i][j].g<176){
                green[10]++;
            }
            else if (im[i][j].g>=176 && im[i][j].g<192){
                green[11]++;
            }
            else if (im[i][j].g>=192 && im[i][j].g<208){
                green[12]++;
            }
            else if (im[i][j].g>=208 && im[i][j].g<224){
                green[13]++;
            }
            else if (im[i][j].g>=224 && im[i][j].g<240){
                green[14]++;
            }
            else if (im[i][j].g>=240 && im[i][j].g<256){
                green[15]++;
            }
            //Red
            if (im[i][j].r<16){
                red[0]++;
            }
            else if (im[i][j].r>=16 && im[i][j].r<32){
                red[1]++;
            }
            else if (im[i][j].r>=32 && im[i][j].r<48){
                red[2]++;
            }
            else if (im[i][j].r>=48 && im[i][j].r<64){
                red[3]++;
            }
            else if (im[i][j].r>=64 && im[i][j].r<80){
                red[4]++;
            }
            else if (im[i][j].r>=80 && im[i][j].r<96){
                red[5]++;
            }
            else if (im[i][j].r>=96 && im[i][j].r<112){
                red[6]++;
            }
            else if (im[i][j].r>=112 && im[i][j].r<128){
                red[7]++;
            }
            else if (im[i][j].r>=128 && im[i][j].r<144){
                red[8]++;
            }
            else if (im[i][j].r>=144 && im[i][j].r<160){
                red[9]++;
            }
            else if (im[i][j].r>=160 && im[i][j].r<176){
                red[10]++;
            }
            else if (im[i][j].r>=176 && im[i][j].r<192){
                red[11]++;
            }
            else if (im[i][j].r>=192 && im[i][j].r<208){
                red[12]++;
            }
            else if (im[i][j].r>=208 && im[i][j].r<224){
                red[13]++;
            }
            else if (im[i][j].r>=224 && im[i][j].r<240){
                red[14]++;
            }
            else if (im[i][j].r>=240 && im[i][j].r<256){
                red[15]++;
            }
            
        }
    }

    printHist("\nRed", red, pxcount);
    printHist("Green", green, pxcount);
    printHist("Blue", blue, pxcount);

    fclose(bmpfile);
    if (outopen==1){
        fclose(out);
    }
    return 0;
}