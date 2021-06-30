#ifndef Compass_HMC5883L_h
#define Compass_HMC5883L_h

#include "Arduino.h"

/*
  By: Riza Çelik
  Created on: 12/05/2021
  License: OSHW 1.0, http://freedomdefined.org/OSHW

  Uno		A4 (SDA), A5 (SCL)
  Mega2560	20 (SDA), 21 (SCL)
  Leonardo	2 (SDA), 3 (SCL)
  Due		20 (SDA), 21 (SCL), SDA1, SCL1
  STM32		PB7 (SDA),  PB6 (SCL)

  https://jensd.dk/cansat/gy80gy87gy88gy91/datasheet/HMC5883L.pdf
  https://jensd.dk/cansat/gy80gy87gy88gy91/datasheet/MPU6050.pdf
  https://jensd.dk/cansat/gy80gy87gy88gy91/datasheet/MPU9250.pdf
  https://jensd.dk/cansat/gy80gy87gy88gy91/datasheet/BMP180.pdf
  https://jensd.dk/cansat/gy80gy87gy88gy91/datasheet/BMP085.pdf
  https://jensd.dk/cansat/gy80gy87gy88gy91/datasheet/ADXL345.pdf
  https://jensd.dk/cansat/gy80gy87gy88gy91/datasheet/L3G4200D.pdf
*/

#define HMC5883L 0x1E // I2C 7bit address of HMC5883
#define scale 0.92f;

class Compass_HMC5883L
{
    public:

  bool begin(void);

  void  setOffset(int xo, int yo);

  float  getX(void);
  float  getY(void);
  float  getZ(void);

    private:

  int xOffset, yOffset;
  int16_t readRegister16(uint8_t reg);
};

#endif