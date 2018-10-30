#include<xc.h>           
#include<sys/attribs.h> 
#include<stdio.h>
#include "ST7735.c"
#include "ST7735.h"
#include "i2c.h"
#include "imu.h"

float a;
float b;
signed short x_c(signed short x){
    
    a = x*60*0.00006;
    signed char z = a;
    return z;
}
signed short y_c(signed short y){
    
    b = y*80*0.00006;
    signed char v = b;
    return v;
}

void drawxbar(unsigned short x, unsigned short y, signed short xexcel){
    int i;
    int j;
    signed char c = x_c(xexcel);
    if (c>=0){
        for (i = 0; i<60;i++){
            for (j = 0; j< 5;j++){
                if (i<c){
                    LCD_drawPixel(x+i,y+j,BLACK);
                }
                else {
                    LCD_drawPixel(x+i,y+j,WHITE);
                }
            }
        } 
   }
    else{
        for (i = 0; i<60;i++){
            for (j = 0; j< 5;j++){
                if (i<abs(c)){
                    LCD_drawPixel(x-i,y+j,BLACK);
                }
                else {
                    LCD_drawPixel(x-i,y+j,WHITE);
                }
            }
        }
        
    }
         
}
void drawybar(unsigned short x, unsigned short y, signed short yexcel){
    int i;
    int j;
    signed char e = y_c(yexcel);
    if (e>=0){
        for (i = 0; i<80;i++){
            for (j = 0; j< 5;j++){
                if (i<e){
                    LCD_drawPixel(x+j,y+i,BLACK);
                }
                else {
                    LCD_drawPixel(x+j,y+i,WHITE);
                }
            }
        } 
   }
    
    else{
        for (i = 0; i<80;i++){
            for (j = 0; j< 5;j++){
                if (i<abs(e)){
                    LCD_drawPixel(x+j,y-i,BLACK);
                }
                else {
                    LCD_drawPixel(x+j,y-i,WHITE);
                }
            }
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
    LATAbits.LATA4 = 0; 
    
    SPI1_init();
    LCD_init();
    LCD_clearScreen(WHITE);
    imu_init();
    __builtin_enable_interrupts();
    _CP0_SET_COUNT(0);
    
    unsigned short a = 64;
    unsigned short b = 80;
    unsigned char r[14];
    while(1){
        
            I2Cmultipleread(r); 
            _CP0_SET_COUNT(0);
            LATAbits.LATA4 = 0;           
            drawxbar(a,b,accelX(r));
            drawybar(a,b,accelY(r));         
            while(_CP0_GET_COUNT() < (12000000/2/5)) {} 
            LATAbits.LATA4 = 1;
        
    }
    
}
      
