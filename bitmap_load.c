//#link "image.c" #8bitworkshop needs this
#include <stdint.h>
#include <cbm.h>

// VIC registers
#define D011 (*(char*)0xD011)
#define D016 (*(char*)0xD016)
#define DD00 (*(char*)0xDD00)
#define D018 (*(char*)0xD018)
#define D020 (*(char*)0xD020)
#define D021 (*(char*)0xD021)

char *imgsrc;
char *imgdest;

extern const char bitmapdata[];

void copymem(char* src, char* dest, int length) {
    int i;  // Declare at the start
    for (i = 0; i < length; i++) {
        *(dest + i) = *(src + i);
    }
}

int main() {
    char *imgsrc;
    char *imgdest;

    (*(char*)0xD011) = 0x3B;  // 25 rows=
    (*(char*)0xD016) = 0x1B;  // 40 columns multicolor mode
    (*(char*)0xDD00) = 0x02;  // VIC bank ($4000-$7FFF)
    (*(char*)0xD018) = 0x80;  // VIC screen to $6000
    (*(char*)0xD020) = 0x00;  // border color
    (*(char*)0xD021) = 0x00;  // background color
    
    // chardata
    imgsrc = (char*)&bitmapdata[0];  // chardata is at pos0
    imgdest = (char*)0x4000;
    copymem(imgsrc, imgdest, 2000); 

    // screendata
    imgsrc = (char*)&bitmapdata[8000];  // bitmapdata + 8000
    imgdest = (char*)0x6000;
    copymem(imgsrc, imgdest, 1000);     

    // colordata
    imgsrc = (char*)&bitmapdata[9000];   // bitmapdata + 8k + 1k
    imgdest = (char*)0xd800;
    copymem(imgsrc, imgdest, 1000);  // src,dst,size_in_bits

    while(1) { }

    return 0;
}
