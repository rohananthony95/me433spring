#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h> 
#include<stdio.h>
#include "ST7735.c"
#include "ST7735.h"
#pragma config DEBUG = OFF // no debugging
#pragma config JTAGEN = OFF // no\ jtag
#pragma config ICESEL = ICS_PGx1 // use PGED1 and PGEC1
#pragma config PWP = OFF // no write protect
#pragma config BWP = OFF // no boot write protect
#pragma config CP = OFF // no code protect

// DEVCFG1
#pragma config FNOSC = PRIPLL // use primary oscillator with pll
#pragma config FSOSCEN = OFF // turn off secondary oscillator
#pragma config IESO = OFF // no switching clocks
#pragma config POSCMOD = HS // high speed crystal mode
#pragma config OSCIOFNC = OFF // disable secondary osc
#pragma config FPBDIV = DIV_1 // divide sysclk freq by 1 for peripheral bus clock
#pragma config FCKSM = CSDCMD // do not enable clock switch
#pragma config WDTPS = PS1 // use slowest wdt
#pragma config WINDIS = OFF // wdt no window mode
#pragma config FWDTEN = OFF // wdt disabled
#pragma config FWDTWINSZ = WINSZ_25 // wdt window at 25%

// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz crystal
#pragma config FPLLIDIV = DIV_2 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = MUL_24 // multiply clock after FPLLIDIV
#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 48MHz
#pragma config UPLLIDIV = DIV_2 // divider for the 8MHz input clock, then multiplied by 12 to get 48MHz for USB
#pragma config UPLLEN = ON // USB clock on

// DEVCFG3
#pragma config USERID = 0b1111000011110000 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = OFF // allow multiple reconfigurations
#pragma config IOL1WAY = OFF // allow multiple reconfigurations
#pragma config FUSBIDIO = OFF // USB pins controlled by USB module
#pragma config FVBUSONIO = OFF // USB BUSON controlled by USB module
#define CSbits LatBbits.LatB7 
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

int main() {
    __builtin_disable_interrupts();

    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;
    
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;

    // do your TRIS and LAT commands here

    
    
    TRISBbits.TRISB4 = 1;
    TRISAbits.TRISA4 = 0;
    LATAbits.LATA4 = 1; 
    
    SPI1_init();
    LCD_init();
    LCD_clearScreen(WHITE);
    
    __builtin_enable_interrupts();
    _CP0_SET_COUNT(0);
    unsigned short a = 28;
    unsigned short b = 32;
    int z = 0;
    float q;
    char fps[19];
    
    
    while(1){
        
        while (z<100){
        _CP0_SET_COUNT(0);
        z++;
        sprintf(message,"Hello World %d", z);
        draw_string(a,b,BLACK,message);
        progress_bar(20,42,100,z );
        sprintf(fps,"fps: %5.1f",q);
        draw_string(28,60,BLACK,fps);           
        q = 48000000.0/_CP0_GET_COUNT();
        while(_CP0_GET_COUNT() < (2400000)) {}
        }
    }
    
}
      