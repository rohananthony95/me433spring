#include <xc.h>
#include "ST7735.h"
#include "hw7.h"

char message[19];
void LCD_drawchar(unsigned short x, unsigned short y, unsigned short color, char c){
    int ii;
    int jj;
    if (x<124 | y<152){
        for (ii=0;ii<5;ii++){
            for (jj=0;jj<8;jj++){
                if (ASCII[c - 0x20][ii]>>jj & 0x1){
                    LCD_drawPixel(x+ii,y+jj, color);
                }
                else {
                    LCD_drawPixel(x+ii,y+jj, WHITE);
                }
            }
        }
    }
}

void draw_string(unsigned short x, unsigned short y, unsigned short color, char *z){
    int i = 0;
    while (z[i]){
        LCD_drawchar((x+6*i),y,color,z[i]);
        i++;
    }
}

void progress_bar(unsigned short x, unsigned short y, int length, int pos){
    int a;
    int b;
    for (a = 0; a < pos; a++){
        for (b = 0; b<8;b++){
            LCD_drawPixel(x+a,y+b,BLUE);
            
        }
        
    }
    for (a = 0; a < (length - pos); a++){
        for (b = 0; b<8;b++){
            LCD_drawPixel(x+a + pos,y+b,RED );
            
        }
        
    }
    
}
