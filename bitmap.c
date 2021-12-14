#include <stdio.h>
#include <stdlib.h>     // for exit
#include <unistd.h>     // for open/close
#include <fcntl.h>      // for O_RDWR
#include <sys/ioctl.h>  // for ioctl
#include <sys/mman.h>
#include <linux/fb.h>   // for fb_var_screeninfo, FBIOGET_VSCREENINFO
#include "bitmap.h"

#define FBDEV_FILE  "/dev/fb0"
#define BIT_VALUE_24BIT   24

static char *pDib;
static int fbfd;
static int fbHeight = 0;
static int fbWidth = 0;
static unsigned long *pfbmap;
static struct fb_var_screeninfo fbInfo;
static struct fb_fix_screeninfo fbFixInfo;
static int currentEmptyBufferPos = 0; //1 Pixel 4Byte Framebuffer

#define PFBSIZE 			(fbHeight*fbWidth*sizeof(unsigned long)*2)	//Double Buffering
#define DOUBLE_BUFF_START	(fbHeight*fbWidth)	///Double Swaping

int show_bmp(char *path){
    int screen_width;
	int screen_height;
	int bits_per_pixel;
	int line_length;
	int cols = 0, rows = 0;
	char* data;

    if(fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) <0 ){
        printf("FrameBuffer init fail\r\n");
        return 0;
    }

    fb_clear();
    if(read_bmp(path, &data, &cols, &rows) <0 ){
        printf("file open fail\r\n");
        return 0;
    }

    fb_write(data, cols, rows);
    close_bmp();
    fb_close();
    return 0;
}

int read_bmp(char *filename, char **data, int *cols, int *rows)
{
    BITMAPFILEHEADER    bmpHeader;
    BITMAPINFOHEADER    *bmpInfoHeader;
    unsigned int    size;
    unsigned char   magicNum[2];
    int     nread;
    FILE    *fp;

    fp  =  fopen(filename, "rb");
    if(fp == NULL) {
        printf("ERROR\n");
        return;
    }

    // identify bmp file
    magicNum[0]   =   fgetc(fp);
    magicNum[1]   =   fgetc(fp);
    printf("magicNum : %c%c\n", magicNum[0], magicNum[1]);

    if(magicNum[0] != 'B' && magicNum[1] != 'M') {
        printf("It's not a bmp file!\n");
        fclose(fp);
        return;
    }

    nread   =   fread(&bmpHeader.bfSize, 1, sizeof(BITMAPFILEHEADER), fp);
    size    =   bmpHeader.bfSize - sizeof(BITMAPFILEHEADER);
    *pDib   =   (unsigned char *)malloc(size);      // DIB Header(Image Header)
    fread(*pDib, 1, size, fp);
    bmpInfoHeader   =   (BITMAPINFOHEADER *)*pDib;

    printf("nread : %d\n", nread);
    printf("size : %d\n", size);

    // check 24bit
    if(BIT_VALUE_24BIT != (bmpInfoHeader->biBitCount))     // bit value
    {
        printf("It supports only 24bit bmp!\n");
        fclose(fp);
        return;
    }

    *cols   =   bmpInfoHeader->biWidth;
    *rows   =   bmpInfoHeader->biHeight;
    *data   =   (char *)(*pDib + bmpHeader.bfOffBits - sizeof(bmpHeader) - 2);
    fclose(fp);
    return 0;
}

int close_bmp(void)     // DIB(Device Independent Bitmap)
{
    free(*pDib);
    return 0;
}

int fb_init(int *screen_width, int *screen_height, int *bits_per_pixel, int *line_length){
    struct fb_fix_screeninfo fbfix;

    if( (fbfd = open(FBDEV_FILE, O_RDWR)) < 0)
    {
        printf("%s: open error\n", FBDEV_FILE);
        close(fbfd);
        exit(1);
    }

    if( ioctl(fbfd, FBIOGET_VSCREENINFO, &fbInfo) )
    {
        printf("%s: ioctl error - FBIOGET_VSCREENINFO \n", FBDEV_FILE);
        close(fbfd);
        exit(1);
    }

    if( ioctl(fbfd, FBIOGET_FSCREENINFO, &fbFixInfo) )
    {
        printf("%s: ioctl error - FBIOGET_FSCREENINFO \n", FBDEV_FILE);
        close(fbfd);
        exit(1);
    }

    if (fbInfo.bits_per_pixel != 32)
    {
        fprintf(stderr, "bpp is not 32\n");
        exit(1);
    }

    fbWidth = *screen_width = fbInfo.xres;
    fbHeight = *screen_height = fbInfo.yres;
    *bits_per_pixel = fbInfo.bits_per_pixel;
    *line_length = fbFixInfo.line_length;

    pfbmap  =   (unsigned char *)
    mmap(0, PFBSIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((unsigned)pfbmap == (unsigned)-1)
    {
        perror("fbdev mmap\n");
        close(fbfd);
        exit(1);
    }

    #ifdef ENABLED_DOUBLE_BUFFERING 
            currentEmptyBufferPos = DOUBLE_BUFF_START;
    #else
            currentEmptyBufferPos = 0;
    #endif

    return -1;
}

int fb_clear(void){
    int coor_y = 0; int coor_x = 0;
    for(coor_y = 0; coor_y < fbHeight; coor_y++){
        unsigned long *ptr = pfbmap + currentEmptyBufferPos + (fbWidth * coor_y);
        for(coor_x = 0; coor_x < fbWidth; coor_x ++){
            *ptr ++ = 0x000000;
        }
    }
    #ifdef ENABLED_DOUBLE_BUFFERING
        fb_doubleBufSwap();
    #endif

    return 0;
}

int fb_doubleBufSwap(void){
    if(currentEmptyBufferPos == 0){
        fbInfo.yoffset = 0;
        currentEmptyBufferPos = DOUBLE_BUFF_START;
    }
    else{
        fbInfo.yoffset = fbHeight;
        currentEmptyBufferPos = 0;
    }
    ioctl(fbfd, FBIOPUT_VSCREENINFO, &fbInfo);
    return 0;
}

int fb_close(void){
    printf("Memory UnMapped!\r\n");
    munmap(pfbmap, PFBSIZE);
    printf("CloseFB\r\n");
    close(fbfd);
    return 0;
}

int fb_write_reverse(char* picData, int picWidth, int picHeight){
    int coor_x = 0; int coor_y = 0;
    int targetHeight = (fbHeight<picHeight)?fbHeight:picHeight;	//if Screen과 파일 사이즈가 안맞으면
	int targetWidth = (fbWidth<picWidth)?fbWidth:picWidth;		//if Screen과 파일 사이즈가 안맞으면
	
	for(coor_y = 0; coor_y < targetHeight; coor_y++) 
	{
		int bmpYOffset = coor_y*picWidth*3; ///Every 1Pixel requires 3Bytes.
		int bmpXOffset = 0;
		for (coor_x=0; coor_x < targetWidth; coor_x++)
		{
			//BMP: B-G-R로 인코딩 됨, FB: 0-R-G-B로 인코딩 됨.
			pfbmap[coor_y*fbWidth+ (coor_x) + currentEmptyBufferPos] = 
				((unsigned long)(picData[bmpYOffset+bmpXOffset+0])<<16) 	+
				((unsigned long)(picData[bmpYOffset+bmpXOffset+1])<<8) 		+
				((unsigned long)(picData[bmpYOffset+bmpXOffset+2]));
			bmpXOffset+=3;	//Three Byte.
		}
    }	
	#ifdef ENABLED_DOUBLE_BUFFERING
		fb_doubleBufSwap();
	#endif	

    return 0;
}

int fb_write(char* picData, int picWidth, int picHeight)
{
	int coor_y=0;
	int coor_x=0;
	int targetHeight = (fbHeight<picHeight)?fbHeight:picHeight;	//if Screen과 파일 사이즈가 안맞으면
	int targetWidth = (fbWidth<picWidth)?fbWidth:picWidth;		//if Screen과 파일 사이즈가 안맞으면
	
	for(coor_y = 0; coor_y < targetHeight; coor_y++) 
	{
		int bmpYOffset = coor_y*picWidth*3; ///Every 1Pixel requires 3Bytes.
		int bmpXOffset = 0;
		for (coor_x=0; coor_x < targetWidth; coor_x++)
		{
			//BMP: B-G-R로 인코딩 됨, FB: 0-R-G-B로 인코딩 됨.
			pfbmap[coor_y*fbWidth+ (fbWidth-coor_x) + currentEmptyBufferPos] = 
				((unsigned long)(picData[bmpYOffset+bmpXOffset+2])<<16) 	+
				((unsigned long)(picData[bmpYOffset+bmpXOffset+1])<<8) 		+
				((unsigned long)(picData[bmpYOffset+bmpXOffset+0]));
			bmpXOffset+=3;	//Three Byte.
		}
    }	
	#ifdef ENABLED_DOUBLE_BUFFERING
		fb_doubleBufSwap();
	#endif

    return 0;
}
