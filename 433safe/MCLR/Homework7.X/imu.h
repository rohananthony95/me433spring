#ifndef LSM6DS33_H__
#define LSM6DS33_H__

#define LSM_ARRAY_LEN 14 

void imu_init(void);
unsigned char WHOAMI(void); 
void I2Cmultipleread(unsigned char *);
signed short Temp(unsigned char * );
signed short gyroX(unsigned char * );
signed short gyroY(unsigned char * );
signed short gyroZ(unsigned char * );
signed short accelX(unsigned char * );
signed short accelY(unsigned char * );
signed short accelZ(unsigned char * );
void drawxbar(unsigned short, unsigned short, signed short);
void drawybar(unsigned short, unsigned short, signed short);
#endif
