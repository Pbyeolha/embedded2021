#ifndef _BITMAP_H
#define _BITMAP_H

int show_bmp(char *path);
int read_bmp(char *filename, char **data, int *cols, int *rows);
int close_bmp(void);
int fb_init(int *screen_width, int *screen_height, int *bits_per_pixel, int *line_length);
void fb_clear(void);
void fb_doubleBufSwap(void);
void fb_write_reverse(char* picData, int picWidth, int picHeight);
void fb_write(char* picData, int picWidth, int picHeight);  

// File Header
typedef struct 
{
    unsigned int    bfSize;         // 4 byte
    unsigned short  bfReserved1;    // 2 byte
    unsigned short  bfReserved2;    // 2 byte
    unsigned int    bfOffBits;      // 4 byte
} BITMAPFILEHEADER;

// Image Header
typedef struct 
{
    unsigned int    biSize;             // 4 byte
    unsigned int    biWidth;            // 4 byte
    unsigned int    biHeight;           // 4 byte
    unsigned short  biPlanes;           // 2 byte
    unsigned short  biBitCount;         // 2 byte
    unsigned int    biCompression;      // 4 byte
    unsigned int    biSizeImage;        // 4 byte
    unsigned int    biXPelsPerMeter;    // 4 byte
    unsigned int    biYPelsPerMeter;    // 4 byte
    unsigned int    biClrUsed;          // 4 byte
    unsigned int    biClrImportant;     // 4 byte
} BITMAPINFOHEADER;

// Color Table
typedef struct 
{
    unsigned char   rgbBlue;        // 1 byte
    unsigned char   rgbGreen;       // 1 byte
    unsigned char   rgbRed;         // 1 byte
    unsigned char   rgbReserved;    // 1 byte
} RGBQUAD;

// Pixel Data
typedef struct 
{
    BITMAPINFOHEADER    bmiHeader;
    RGBQUAD             bmiColors[1];
} BITMAPINFO;

#endif