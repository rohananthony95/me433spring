#include <xc.h>
#include "i2c.h"
#include "i2c.h"
#include "ST7735.h"

void imu_init(void) { 
    i2c_master_setup();   
    i2c_master_start(); 
    i2c_master_send(0x6A << 1);  
    i2c_master_send(0x10);  
    i2c_master_send(0x82);                          
    i2c_master_stop();  

    
    i2c_master_start(); 
    i2c_master_send(0x6A << 1);  
    i2c_master_send(0x11);  
    i2c_master_send(0x88);                         
    i2c_master_stop();  

    
    i2c_master_start(); 
    i2c_master_send(0x6A << 1);  
    i2c_master_send(0x12);  
    i2c_master_send(0x04);                            
    i2c_master_stop();  
}
unsigned char WHOAMI(void) { 
    unsigned char answer;
    i2c_master_start();
    i2c_master_send((0x6A << 1)); 
    i2c_master_send(0x0F);  
    i2c_master_restart(); 
    i2c_master_send((0x6A << 1) | 1); 
    answer = i2c_master_recv(); 
    i2c_master_ack(1); 
    i2c_master_stop();
    return answer;
}

void I2Cmultipleread(unsigned char * readings){
    i2c_master_start();
    i2c_master_send(0x6A << 1);
    i2c_master_send(0x20);
    i2c_master_restart();
    i2c_master_send((0x6A << 1)|1);
    int i;
    for ( i = 0; i < 14;i++){
        readings[i] = i2c_master_recv();
        if (i<13) {
                i2c_master_ack(0); 
            }
        else {
                i2c_master_ack(1); 
            }
    }
    i2c_master_stop();
}
signed short Temp(unsigned char * readings){
    return ((readings[1]<<8) | readings[1]);
}

signed short gyroX(unsigned char * readings){
    return ((readings[3]<<8) | readings[2]);
}
signed short gyroY(unsigned char * readings){
    return ((readings[5]<<8) | readings[4]);
}
signed short gyroZ(unsigned char * readings){
    return ((readings[7]<<8) | readings[6]);
}

signed short accelX(unsigned char * readings){
    return ((readings[9]<<8) | readings[8]);
}
signed short accelY(unsigned char * readings){
    return ((readings[11]<<8) | readings[10]);
}
signed short accelZ(unsigned char * readings){
    return ((readings[13]<<8) | readings[12]);
}
signed short x_c(signed short x){
    float aa;
    aa = x*60*0.00006;
    signed short z = (signed short) aa;
    return z;
}
signed short y_c(signed short y){
    float bb;
    bb = y*80*0.00006;
    signed short v = bb;
    return v;
}