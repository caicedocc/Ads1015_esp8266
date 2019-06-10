/*
**********************************************************
ADS1015_ESP8266.h
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

//---------- Input multiplexer configuration ---------------------
#define MUX_DIF_0_1  (0b00000000)  // Differential AIP=0, AIN=1 (default)
#define MUX_DIF_0_3  (0b00010000)  // Differential AIP=0, AIN=3
#define MUX_DIF_1_3  (0b00100000)  // Differential AIP=1, AIN=3
#define MUX_DIF_2_3  (0b00110000)  // Differential AIP=2, AIN=3
#define MUX_SGL_0    (0b01000000)  // Single AIP=0, AIN=GND
#define MUX_SGL_1    (0b01010000)  // Single AIP=1, AIN=GND
#define MUX_SGL_2    (0b01100000)  // Single AIP=2, AIN=GND
#define MUX_SGL_3    (0b01110000)  // Single AIP=3, AIN=GND
#define MUX_CLEAR    (0b10001111)

//---------- Programable gain amplifier configuration ------------
#define FSR_6144     (0b00000000)  // +/-6.144V (full scale range)
#define FSR_4096     (0b00000010)  // +/-4.096V
#define FSR_2048     (0b00000100)  // +/-2.048V (default)
#define FSR_1024     (0b00000110)  // +/-1.024V
#define FSR_0512     (0b00001000)  // +/-0.512V
#define FSR_0256     (0b00001110)  // +/-0.256V
#define FSR_CLEAR    (0b11110001)

//---------- Data rate setting -----------------------------------
#define DR_128       (0b00000000)  // (Samples per second)
#define DR_250       (0b00100000)
#define DR_490       (0b01000000)
#define DR_920       (0b01100000)
#define DR_1600      (0b10000000)  // (default)
#define DR_2400      (0b10100000)
#define DR_3300      (0b11100000)
#define DR_CLEAR     (0b00011111)

//---------- Corresponding multiplier in Volts (V) ---------------
#define LSB_6144     (0.003f)      // +/-6.144V (LSB size) 
#define LSB_4096     (0.002f)      // +/-4.096V
#define LSB_2048     (0.001f)      // +/-2.048V
#define LSB_1024     (0.0005f)     // +/-1.024V
#define LSB_0512     (0.00025f)    // +/-0.512V
#define LSB_0256     (0.000125f)   // +/-0.256V

class Ads1015_esp8266
{
  private:
    uint8_t   _address;
    uint16_t  _conversionDelay;
    uint8_t   _config[3];
    uint8_t   _conversion[3];
    void      writeConfiguration(void);

  public:
    Ads1015_esp8266(uint8_t address);
    void      begin(uint8_t sda, uint8_t scl);
    void      selectInput(uint8_t mux);
    void      selectGain(uint8_t fsr);
    void      selectRate(uint8_t dr);
    int16_t   readConversion(void);
};
