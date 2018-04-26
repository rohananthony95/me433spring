#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include<math.h>
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

#define CS LATBbits.LATB3
//got these value from matlab 
unsigned char sine_wave[200] = {
135,143,151,159,166,174,181,188,195,202,208,214,220,225,230,234,238,242,245,248,250,252,253,254,254,254,253,252,250,248,245,242,238,234,230,225,220,214,208,202,195,188,181,174,166,159,151,143,135,127,119,111,103,95,88,80,73,66,59,52,46,40,34,29,24,20,16,12,9,6,4,2,1,0,0,0,1,2,4,6,9,12,16,20,24,29,34,40,46,52,59,66,73,80,88,95,103,111,119,127,135,143,151,159,166,174,181,188,195,202,208,214,220,225,230,234,238,242,245,248,250,252,253,254,254,254,253,252,250,248,245,242,238,234,230,225,220,214,208,202,195,188,181,174,166,159,151,143,135,127,119,111,103,95,88,80,73,66,59,52,46,40,34,29,24,20,16,12,9,6,4,2,1,0,0,0,1,2,4,6,9,12,16,20,24,29,34,40,46,52,59,66,73,80,88,95,103,111,119,127
};
unsigned char tri_angle[200] = {
0,3,5,8,10,13,15,18,20,23,26,28,31,33,36,38,41,44,46,49,51,54,56,59,61,64,67,69,72,74,77,79,82,84,87,90,92,95,97,100,102,105,108,110,113,115,118,120,123,125,128,131,133,136,138,141,143,146,148,151,154,156,159,161,164,166,169,172,174,177,179,182,184,187,189,192,195,197,200,202,205,207,210,212,215,218,220,223,225,228,230,233,236,238,241,243,246,248,251,253,253,251,248,246,243,241,238,236,233,230,228,225,223,220,218,215,212,210,207,205,202,200,197,195,192,189,187,184,182,179,177,174,172,169,166,164,161,159,156,154,151,148,146,143,141,138,136,133,131,128,125,123,120,118,115,113,110,108,105,102,100,97,95,92,90,87,84,82,79,77,74,72,69,67,64,61,59,56,54,51,49,46,44,41,38,36,33,31,28,26,23,20,18,15,13,10,8,5,3,0
};

void initspi(void){
    
    RPB2Rbits.RPB2R = 0b0011;
    CS = 1;    
    SPI1CON = 0;              // turn off the spi module and reset it
    SPI1BUF;                  // clear the rx buffer by reading from it
    SPI1BRG = 0x3;            // baud rate to 10 MHz [SPI4BRG = (80000000/(2*desired))-1]
    SPI1STATbits.SPIROV = 0;  // clear the overflow bit
    SPI1CONbits.CKE = 1;      // data changes when clock goes from hi to lo (since CKP is 0)
    SPI1CONbits.MSTEN = 1;    // master operation
    SPI1CONbits.ON = 1;
}
unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}
void setVoltage(char channel, int voltage){
    unsigned char byte_1;
    unsigned char byte_2;
    
    CS = 0; // SPI chip select LOW (active)
    byte_1 = voltage << 4;
    byte_2 = ((channel << 7)|(0b111 << 4))|(voltage >> 4);
    spi_io(byte_1);
    spi_io(byte_2);
    CS = 1;
    
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

    // do your TRIS and LAT commands here

    
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 0; 
    TRISBbits.TRISB4 = 1;
    TRISAbits.TRISA4 = 0;
    LATAbits.LATA4 = 1;
    initspi();
    __builtin_enable_interrupts();
    
    
    
    _CP0_SET_COUNT(0);
    int ii = 0;
     
    int a = 0;
    

    while(1) {
        
        _CP0_SET_COUNT(0);
        for (a = 0; a<200;a++){
            
        
            while (_CP0_GET_COUNT()<24000){}

            setVoltage(0, sine_wave[a]); 
            setVoltage(1, tri_angle[a]);
            
            
        }
        
        
	
    }
}