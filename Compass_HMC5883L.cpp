#include "Arduino.h"
#include <Wire.h>
#include "Compass_HMC5883L.h"

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

bool Compass_HMC5883L::begin()
{
  Wire.begin();
  
  // HMC5883L Setup
  Wire.beginTransmission(HMC5883L);
  // set scale to +/- 1.3 gauss
  // scale = 0.92;    // for 1.3 gauss
  Wire.write(0x01);   // select register address
  Wire.write(0x20);   // write data
  Wire.endTransmission();
  
  Wire.beginTransmission(HMC5883L);
  // set continuous measurement mode
  Wire.write(0x02); // select register address
  Wire.write(0x00); // write data
  Wire.endTransmission();
}

void Compass_HMC5883L::setOffset(int xo, int yo)
{
    xOffset = xo;
    yOffset = yo;
}

float Compass_HMC5883L::getX(void)
{
  float XAxis = ((float)readRegister16(0x03) - xOffset) * scale;
  return XAxis;
}

float Compass_HMC5883L::getY(void)
{
  float YAxis = ((float)readRegister16(0x07) - yOffset) * scale;
  return YAxis;
}

float Compass_HMC5883L::getZ(void)
{
  float ZAxis = (float)readRegister16(0x05) * scale;
  return ZAxis;
}

int16_t Compass_HMC5883L::readRegister16(uint8_t reg)
{
  int16_t value;
  Wire.beginTransmission(HMC5883L);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.beginTransmission(HMC5883L);
  Wire.requestFrom(HMC5883L, 2);
  while (!Wire.available()) {};
  uint8_t vha = Wire.read();
  uint8_t vla = Wire.read();
  Wire.endTransmission();
  value = vha << 8 | vla;
  return value;
}
