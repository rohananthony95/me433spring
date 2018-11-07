#ifndef imu_H__
#define imu_H__

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
#endif
