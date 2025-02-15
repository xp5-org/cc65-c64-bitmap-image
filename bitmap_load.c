//#link "image.c" #8bitworkshop needs this
#include <stdint.h>
#include <cbm.h>

char *imgsrc;
char *imgdest;

extern const char bitmapdata[];

void copymem(char* src, char* dest, int length) {
    int i;
    for (i = 0; i < length; i++) {
        *(dest + i) = *(src + i);
    }
}

int main() {
    // VIC Bank locations
    // $DD00 bank0 $0000-$3fff
    // $DD00 bank1 $4000-$7fff
    // $DD00 bank2 $8000-$bfff
    // $DD00 bank3 $c000-$ffff

    // VIC registers
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
