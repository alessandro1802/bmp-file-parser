#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

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
    printf("    bfType: 0x%x\n", bitmapFileHeader.bfType);
    printf("    bfSize: %d\n", bitmapFileHeader.bfSize);
    printf("    bfReserved1: 0x%x\n", bitmapFileHeader.bfReserved1);
    printf("    bfReserved2: 0x%x\n", bitmapFileHeader.bfReserved2);
    printf("    bfOffBits: %d\n", bitmapFileHeader.bfOffBits);
}

void printInfoHeader(BITMAPINFOHEADER bitmapInfoHeader){
    printf("BITMAPINFOHEADER\n");
    printf("    biSize: %d\n", bitmapInfoHeader.biSize);
    printf("    biWidth: %d\n", bitmapInfoHeader.biWidth);
    printf("    biHeight: %d\n", bitmapInfoHeader.biHeight);
    printf("    biPlanes: %d\n", bitmapInfoHeader.biPlanes);
    printf("    biBitCount: %d\n", bitmapInfoHeader.biBitCount);
    printf("    biCompression: %d\n", bitmapInfoHeader.biCompression);
    printf("    biSizeImage: %d\n", bitmapInfoHeader.biSizeImage);
    printf("    biXPelsPerMeter: %d\n", bitmapInfoHeader.biXPelsPerMeter);
    printf("    biYPelsPerMeter: %d\n", bitmapInfoHeader.biYPelsPerMeter);
    printf("    biClrUsed: %d\n", bitmapInfoHeader.biClrUsed);
    printf("    biClrImportant: %d\n", bitmapInfoHeader.biClrImportant);
}

typedef struct Pixel{
    unsigned char  b;
    unsigned char  g;
    unsigned char  r;
} PIXEL;

void printHist(char* colour, int* arr, int pxcount){
    printf("%s:\n", colour);
    int i = 0;
    float tmp = 100*(float)arr[i]/pxcount;
    printf("    0-15: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("    16-31: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("    32-47: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("    48-63: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("    64-79: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("    80-95: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("    96-111: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("    112-127: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("    128-143: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("    144-159: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("    160-175: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("    176-191: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("    192-207: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("    208-223: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("    224-239: %.2f%%\n", tmp);
    i++;
    tmp = 100*(float)arr[i]/pxcount;
    printf("    240-255: %.2f%%\n", tmp);
}

void printSumPerc(int* red, int* green, int* blue, int pxcount){
    float sumB = 0;
    float sumG = 0;
    float sumR = 0;
    float tmp;
    for (int i=0; i<=15; i++){
        tmp = 100*(float)red[i]/pxcount;
        sumR+=tmp;
        tmp = 100*(float)green[i]/pxcount;
        sumG+=tmp;
        tmp = 100*(float)blue[i]/pxcount;
        sumB+=tmp;
    }
    printf("sumR: %f, sumG: %f, sumB: %f\n", sumR, sumG, sumB);
}

int main(int argc, char* argv[]){
    BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header
    BITMAPINFOHEADER bitmapInfoHeader;

    // Open the file for Reading and validate it
    FILE *bmpfile;
    if (( bmpfile = fopen (argv[1], "rb")) == NULL) {
        fprintf (stderr, "error: file open failed '%s'\n", argv[1]);
        perror ("fopen");
        return 1;
    }

    // Open the file for Writing and validate it
    FILE *out;
    int outopen=1;
    if (( out = fopen (argv[2], "wb")) == NULL) {
        printf("error: failed to open output file ('%s')\n", argv[2]);
        outopen=0;
    }

    // Write the bitmap file header and info header
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, bmpfile);
    fwrite(header, sizeof(unsigned char), 54, out);
    fseek(bmpfile, 0, SEEK_SET );

    // Read the bitmap file header
    //fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, bmpfile);
    fread(&bitmapFileHeader.bfType, 2, 1, bmpfile);
    fread(&bitmapFileHeader.bfSize, 4, 1, bmpfile);
    fread(&bitmapFileHeader.bfReserved1, 2, 1, bmpfile);
    fread(&bitmapFileHeader.bfReserved2, 2, 1, bmpfile);
    fread(&bitmapFileHeader.bfOffBits, 4, 1, bmpfile);

    // Read the bitmap info header
    fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,bmpfile);

    // Print header information
    printFileHeader(bitmapFileHeader);
    printInfoHeader(bitmapInfoHeader);

    if (bitmapInfoHeader.biBitCount!=24 || bitmapInfoHeader.biCompression!=0){
        printf("Histogram calculation is unsupported.\n");
        return 0;
    }

    // colour = [(0-15), (16-31), (32-63)...] 
    int red[16] = {0};
    int green[16] = {0};
    int blue[16] = {0};

    int pxcount=0;
    //double rowsize = floor((bitmapInfoHeader.biBitCount*bitmapInfoHeader.biWidth+31)/32)*4;

    PIXEL im[bitmapInfoHeader.biHeight][bitmapInfoHeader.biWidth];
    PIXEL gray;
    int i, j;
    //for (i = bitmapInfoHeader.biHeight-1; i >= 0; i--) {
    for (i = 0; i <= bitmapInfoHeader.biHeight; i++) {
        for (j = 0; j < bitmapInfoHeader.biWidth; j++) {
            fread(&im[i][j], sizeof(unsigned char), sizeof(PIXEL), bmpfile);
            pxcount++;
            //printf("%d %d %d ", im[i][j].r, im[i][j].g, im[i][j].b);
            // Calculate gray pixel value and write it to the file

            /*char g = im[i][j].r * 1/3 + im[i][j].g * 1/3 + im[i][j].b * 1/3;
            gray.r=g;
            gray.g=g;
            gray.b=g;*/
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
        //printf("\n");
    }
    // 16 32 48 64 80 96 112 128 144 160 176 192 208 224 240 256

    printHist("\nRed", red, pxcount);
    printHist("Green", green, pxcount);
    printHist("Blue", blue, pxcount);

    //printSumPerc(red, green, blue, pxcount);

    fclose(bmpfile);
    if (outopen==1){
        fclose(out);
    }
    return 0;
}