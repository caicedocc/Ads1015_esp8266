/*
**********************************************************
ADS1015_ESP8266.cpp
 A library to use ADS1015 12-bit ADC along with esp8266
 created May 2019
 by Cesar Caicedo Caicedo

Notice: This implementation uses the library brzo_i2c instead
of Wire for reliable I2C comunication at fast mode speeds.
This makes the code dependent of esp8266 MCUs.

Fixed values: Operating mode = single conversion
              Comparator     = disabled
**********************************************************
*/

#include <Arduino.h>
#include <brzo_i2c.h>
#include <Ads1015_esp8266.h>

Ads1015_esp8266::Ads1015_esp8266(uint8_t address)
{
  _address = address;       
  uint16_t  _conversionDelay;
  uint8_t   _config[3];
  uint8_t   _conversion[3];
}

void Ads1015_esp8266::writeConfiguration(void)
{
  brzo_i2c_start_transaction(_address, 400);
  brzo_i2c_write(_config, 3, false);
  brzo_i2c_end_transaction();
  brzo_i2c_start_transaction(_address, 400);
  brzo_i2c_write(_conversion, 1, false);
  brzo_i2c_end_transaction();
}

void Ads1015_esp8266::begin(uint8_t sda, uint8_t scl)
{
  _conversionDelay = 650;           // default delay usecs
  _config[0]     = 0b00000001;      // config register
  _config[1]     = 0b10000101;      // byte1 os=1, mux=000, fsr=010, mode=1
  _config[2]     = 0b10000011;      // byte2 dr=100, c_mode=0, c_pol=0, c_lat=0, c_que=11
  _conversion[0] = 0b00000000;      // conversion register
  _conversion[1] = 0b00000000;      // MSB data
  _conversion[2] = 0b00000000;      // LSB data
  brzo_i2c_setup(sda, scl, 500);    // 500 usec clk stretching timeout
}

void Ads1015_esp8266::selectInput(uint8_t mux)
{
  _config[1] &= MUX_CLEAR;
  _config[1] |= mux;
}

void Ads1015_esp8266::selectGain(uint8_t fsr)
{
  _config[1] &= FSR_CLEAR;
  _config[1] |= fsr;
}

void Ads1015_esp8266::selectRate(uint8_t dr)
{
  _config[2] &= DR_CLEAR;
  _config[2] |= dr;
  switch (dr >> 5)                  // select appropriate delay in usecs
  {
    case (0):
      _conversionDelay = 7838;
      break;
    case (1):
      _conversionDelay = 4025;
      break;
    case (2):
      _conversionDelay = 2066;
      break;
    case (3):
      _conversionDelay = 1112;
      break;
    case (4):
      _conversionDelay = 650;
      break;
    case (5):
      _conversionDelay = 442;
      break;
    case (6):
      _conversionDelay = 329;
      break;
  }
}

int16_t Ads1015_esp8266::readConversion(void)
{
  writeConfiguration();             // start a single conversion
  delayMicroseconds(_conversionDelay);
  brzo_i2c_start_transaction(_address, 400);
  brzo_i2c_read(&_conversion[1], 2, false);
  brzo_i2c_end_transaction();
  uint16_t value = ((_conversion[1] << 8) | _conversion[2]) >> 4;
  if (value > 0x07FF) value |= 0xF000;
  return (int16_t)value;
}
