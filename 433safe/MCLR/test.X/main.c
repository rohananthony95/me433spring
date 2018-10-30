#include<xc.h>           // processor SFR definitions
//#include<math.h>
#include "i2c.h"
#include<sys/attribs.h>  // __ISR macro

// DEVCFG0
#pragma config DEBUG = OFF // no debugging
#pragma config JTAGEN = OFF // no jtag
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
#pragma config WDTPS = PS1 // use slowest wdt if this doesnt work use PS1048576
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
#pragma config USERID = 0b0011011010011101 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = OFF // allow multiple reconfigurations
#pragma config IOL1WAY = OFF // allow multiple reconfigurations
#pragma config FUSBIDIO = OFF // USB pins controlled by USB module
#pragma config FVBUSONIO = OFF // USB BUSON controlled by USB module
#define SLAVE_ADDR 0x20

void set_expander(char pin, char level){
    i2c_master_start();
    i2c_master_send(SLAVE_ADDR << 1);
    i2c_master_send(0x0A); //LAT reg
    
//    unsigned char pin_info;
    
    
    i2c_master_send(level<< pin);
    i2c_master_stop();
}
unsigned char get_expander(void){
    unsigned char gpio_state;
    i2c_master_start();
    
    i2c_master_send(SLAVE_ADDR << 1);
    i2c_master_send(0x09);
    i2c_master_restart();
    
    i2c_master_send((SLAVE_ADDR << 1)|1);
    gpio_state = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
    
    return gpio_state;
}
void init_expander(void){
    i2c_init();
    i2c_master_start(); //S
    i2c_master_send(SLAVE_ADDR << 1); //OP + W
    i2c_master_send(0x00); //iodir REG ADDR
    i2c_master_send(0xF0); //data value
    i2c_master_stop();
    
    /*
    i2c_master_start();
    i2c_master_send(WRITE_ADDRESS); //OP + W
    i2c_master_send(0x0A); //GPIO LAT register
    i2c_master_send(0x01); //data to put to register
    i2c_master_stop();
     * */
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
    ANSELBbits.ANSB2 = 0; //turn off analog
    ANSELBbits.ANSB3 = 0;

    // do your TRIS and LAT commands here
//    TRISBbits.TRISB4 = 0; // B4 is output 
//    TRISAbits.TRISA4 = 1; // A4 is input
//    LATBbits.LATB4 = 1; 
    init_expander();
    __builtin_enable_interrupts();

    /*Configure interrupt timer, Timer2*/
// __builtin_disable_interrupts(); // disable interrupts while configuring controller interrupt
//    PR2 = 37499;                    //             set period register
//    TMR2 = 0;                       //             initialize count to 0
//    T2CONbits.TCKPS = 0b111;            //             set prescaler to 256
//    T2CONbits.ON = 1;               //             turn on Timer1
//    IPC2bits.T2IP = 5;              // INT step 4: priority
//    IPC2bits.T2IS = 0;              //             subpriority
//    IFS0bits.T2IF = 0;              // INT step 5: clear interrupt flag
//    IEC0bits.T2IE = 1;              // INT step 6: enable interrupt
//  __builtin_enable_interrupts();  // INT step 7: enable interrupts at CPU
//    
    
    
    
    unsigned char button_state;
    
    while(1) {
        button_state = (get_expander() >>7);
        
        if(button_state){
            set_expander(0,1);
        } else  {
            set_expander(0,0);
        }
    }
}
