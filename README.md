# Ads1015_esp8266

A library to use ADS1015 12-bit ADC along with esp8266 MCUs.

## Notice

This implementation uses the library [brzo_i2c](https://github.com/pasko-zh/brzo_i2c) instead of Wire for reliable I2C comunication at fast mode speeds.
It makes the code dependent of esp8266 MCUs !!!

## Prerequisites

You must install [brzo_i2c](https://github.com/pasko-zh/brzo_i2c) library in order for this to work.

## Fixed values

The ADS1015 is always operated in continuous conversion operating mode and comparator disabled. For further information consult TI´s [ADS1015 datasheet](http://www.ti.com/lit/gpn/ADS1015).

I2C software communication between master and slave is set at 400kHz clock speed.

## Functions

Providing you ```#include <Ads1015_esp8266.h>``` library in your sketch then just instantiate an object of type:

```Ads1015_esp8266  myName(uint8_t Address);``` where Address is one of the following slave addresses:

* 0x48	address pin of ADS1015 connected to GND
* 0x49	...pin connected to VCC
* 0x50	...pin connected to SDA
* 0x51	...pin connected to SCL

then you will have five functions available: ```begin```, ```selectInput```, ```selectGain```, ```selectRate``` and ```readConversion```.

### begin

The very first function you must call in order to start continuous conversion and correctly setup software I2C comunication with the slave ADS1015.

```
begin(uint8_t sda, uint8_t scl);
```
Where
* SDA pin of your esp8266.
* SCL pin...

Example: Start conversions and setup I2C communication using NodeMCU V1.0 ```begin(D2, D1);```

### selectInput

Select one analog input to convert by changing the configuration of input multiplexer (MUX). The ADS1015 features an MUX that allows two differential or four single-ended input measurements. WARNING: Analog input voltages must never exceed the limits given in [ADS1015 datasheet](http://www.ti.com/lit/gpn/ADS1015).

```
selectInput(uint8_t mux);
```

Where mux is one of the following definitions:
* MUX_DIF_0_1   Differential AIP=0, AIN=1 (default)
* MUX_DIF_0_3   Differential AIP=0, AIN=3
* MUX_DIF_1_3   Differential AIP=1, AIN=3
* MUX_DIF_2_3   Differential AIP=2, AIN=3
* MUX_SGL_0     Single AIP=0, AIN=GND
* MUX_SGL_1     Single AIP=1, AIN=GND
* MUX_SGL_2     Single AIP=2, AIN=GND
* MUX_SGL_3     Single AIP=3, AIN=GND.

Example: Select analog differential input between pins A2+ and A3- ```selectInput(MUX_DIF_2_3);```

### selectGain

Select the full scale range (FSR) of measurements by changing the configuration of the programmable gain amplifier (PGA). The PGA offers six input ranges from ±256 mV to ±6.144 V.

```
selectGain(uint8_t fsr);
```

Where fsr is one of the following definitions:
* FSR_6144      +/-6.144V
* FSR_4096      +/-4.096V
* FSR_2048      +/-2.048V (default)
* FSR_1024      +/-1.024V
* FSR_0512      +/-0.512V
* FSR_0256      +/-0.256V

Example: Select input range of +/-1.024V ```selectGain(FSR_1024);```

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
