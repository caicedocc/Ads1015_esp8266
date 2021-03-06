# Ads1015_esp8266

A library to use ADS1015 12-bit ADC along with esp8266 MCUs.  
Created May 2019  
by Cesar Caicedo Caicedo  
 
## Notice

This implementation uses the library [brzo_i2c](https://github.com/pasko-zh/brzo_i2c) instead of Wire for reliable I2C comunication at fast mode speeds.  
It makes the code dependent of esp8266 MCUs.

## Prerequisites

You must install [brzo_i2c](https://github.com/pasko-zh/brzo_i2c) library in order for this to work.

## Fixed values

- The ADS1015 is always operated in single conversion mode and comparator disabled.  
- I2C software communication between master and slave is set at 400kHz clock speed.  

## Functions

Providing you `#include <Ads1015_esp8266.h>` library in your sketch then just instantiate an object of type  
`Ads1015_esp8266  whateverName(uint8_t Address);` where Address is one of the following slave addresses:

- `0x48`	address pin of ADS1015 connected to GND
- `0x49`	...pin connected to VCC
- `0x50`	...pin connected to SDA
- `0x51`	...pin connected to SCL

next you will have five functions available: `begin`, `selectInput`, `selectGain`, `selectRate` and `readConversion`.

## begin

The very first function you must call in order to setup software I2C comunication with the slave ADS1015.

```
begin(uint8_t sda, uint8_t scl);
```
Where
- `sda` I2C data pin of your esp8266.
- `scl` I2C clock pin...

_Example:_ Setup I2C communication using NodeMCU V1.0 `begin(D2, D1);`

## selectInput

Select one analog input to convert by changing configuration of the input multiplexer (MUX).  
The MUX allows two differential or four single-ended input measurements.  

__WARNING__: Analog input voltages must never exceed limits given in [ADS1015 datasheet](http://www.ti.com/lit/gpn/ADS1015).

```
selectInput(uint8_t mux);
```

Where `mux` is one of the following definitions:
- `MUX_DIF_0_1`   Differential AIP=0, AIN=1 (default)
- `MUX_DIF_0_3`   Differential AIP=0, AIN=3
- `MUX_DIF_1_3`   Differential AIP=1, AIN=3
- `MUX_DIF_2_3`   Differential AIP=2, AIN=3
- `MUX_SGL_0`     Single-ended AIP=0, AIN=GND
- `MUX_SGL_1`     Single-ended AIP=1, AIN=GND
- `MUX_SGL_2`     Single-ended AIP=2, AIN=GND
- `MUX_SGL_3`     Single-ended AIP=3, AIN=GND

_Example:_ Select analog differential input between pins A2+ and A3- `selectInput(MUX_DIF_2_3);`

## selectGain

Select full scale range (FSR) of measurements by changing configuration of the programmable gain amplifier (PGA).  
The PGA offers six input ranges from ±256 mV to ±6.144 V.

```
selectGain(uint8_t fsr);
```

Where `fsr` is one of the following definitions:
- `FSR_6144`      +/-6.144V
- `FSR_4096`      +/-4.096V
- `FSR_2048`      +/-2.048V (default)
- `FSR_1024`      +/-1.024V
- `FSR_0512`      +/-0.512V
- `FSR_0256`      +/-0.256V

_Example:_ Select input range of +/-1.024V `selectGain(FSR_1024);`

## selectRate

Select conversion data rate in samples per second.  

__NOTICE:__ It relies on you the management of the _effective sampling rate_ that is the real speed at which data is acquired by your sketch.

```
selectRate(uint8_t dr);
```

Where `dr` is one of the following definitions:
- `DR_128`        128 SPS
- `DR_250`
- `DR_490`
- `DR_920`
- `DR_1600`       (default)
- `DR_2400`
- `DR_3300`

_Example:_ Select 3300 SPS data rate `selectRate(DR_3300);`

## readConversion

This function returns a number of type `int16_t` which represents the amplitude of signal measured at selected analog input.

```
int16_t   readConversion();
```

To convert this number into voltage you have to multiply it by its corresponding least significant bit size (LSB).  
This multiplier factor is stored in the following definitions:

- `LSB_6144`      +/-6.144V
- `LSB_4096`      +/-4.096V
- `LSB_2048`      +/-2.048V
- `LSB_1024`      +/-1.024V
- `LSB_0512`      +/-0.512V
- `LSB_0256`      +/-0.256V

_Example:_ Read the previously selected analog input, convert it to Volts and store the result in a variable called `voltage`  

`float voltage = whateverName.readConversion() * LSB_1024;`  

__NOTICE:__ Be careful to choose the same FSR used in the function `selectGain` for the LSB. For example the corresponding multiplier for a `FSR_4096` is `LSB_4096`.  
