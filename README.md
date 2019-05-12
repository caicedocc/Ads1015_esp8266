# Ads1015_esp8266

A library to use ADS1015 12-bit ADC along with esp8266 MCUs

## Notice

This implementation uses the library [brzo_i2c](https://github.com/pasko-zh/brzo_i2c) instead of Wire for reliable I2C comunication at fast mode speeds.
This makes the code dependent of esp8266 MCUs !!!

## Prerequisites

You must install [brzo_i2c](https://github.com/pasko-zh/brzo_i2c) library in order for this to work.

## Fixed values

The ADS1015 is always operated in continuous conversion operating mode and comparator disabled.

## Functions

Providing you ```#include <Ads1015_esp8266.h>``` library in your sketch then just instantiate an object of type:
```Ads1015_esp8266  myName(uint8_t Address);``` where Address is one of the following slave addresses:

* 0x48	address pin of ADS1015 connected to GND
* 0x49	      	pin connected to VCC
* 0x50		      pin connected to SDA
* 0x51		      pin connected to SCL

then you will have the following five functions available:

### begin

Explain how to run the automated tests for this system

### selectInput

Explain what these tests test and why

```
Give an example
```
### selectGain

Explain what these tests test and why

```
Give an example
```
### selectRate

Explain what these tests test and why

```
Give an example
```
### readConversion

Explain what these tests test and why

```
Give an example
```
