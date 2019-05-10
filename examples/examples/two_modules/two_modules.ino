/*
 This example shows how to use two ADS1015 modules simultaneously 
 to read a single ended analog channel in the first one and a differential
 channel in the other one. Each module uses different amplifier gain but
 same default data rate 1600 SPS.
  created May 2019
  by Cesar Caicedo Caicedo

  ---------- Input multiplexer configuration ---------------------
  MUX_DIF_0_1   Differential AIP=0, AIN=1 (default)
  MUX_DIF_0_3   Differential AIP=0, AIN=3
  MUX_DIF_1_3   Differential AIP=1, AIN=3
  MUX_DIF_2_3   Differential AIP=2, AIN=3
  MUX_SGL_0     Single AIP=0, AIN=GND
  MUX_SGL_1     Single AIP=1, AIN=GND
  MUX_SGL_2     Single AIP=2, AIN=GND
  MUX_SGL_3     Single AIP=3, AIN=GND
  ---------- Programable gain amplifier configuration ------------
  FSR_6144      +/-6.144V (full scale range)
  FSR_4096      +/-4.096V
  FSR_2048      +/-2.048V (default)
  FSR_1024      +/-1.024V
  FSR_0512      +/-0.512V
  FSR_0256      +/-0.256V
  ---------- Data rate setting -----------------------------------
  DR_128        (Samples per second)
  DR_250
  DR_490
  DR_920
  DR_1600       (default)
  DR_2400
  DR_3300
  ---------- Corresponding multiplier in Volts (V) ---------------
  LSB_6144      +/-6.144V (LSB size)
  LSB_4096      +/-4.096V
  LSB_2048      +/-2.048V
  LSB_1024      +/-1.024V
  LSB_0512      +/-0.512V
  LSB_0256      +/-0.256V
*/

#include <Ads1015_esp8266.h>
Ads1015_esp8266 myADC1(0x48);                // slave address pin connected to GND (module 1)
Ads1015_esp8266 myADC2(0x49);                // slave address pin connected to VCC (module 2)
float voltage1, voltage2;

void setup()
{
  Serial.begin(9600);
  myADC1.begin(D2, D1);                      // SDA = D2, SCL = D1 (nodeMCU v1.0)
  myADC1.selectGain(FSR_6144);               // set amplifier scale range +/-6.144V (module 1)
  myADC1.selectInput(MUX_SGL_1);             // analog input A1 single ended (module 1)
  myADC2.begin(D2, D1);
  myADC2.selectGain(FSR_4096);               // set amplifier scale range +/-4.096V (module 2)
  myADC2.selectInput(MUX_DIF_2_3);           // differential input between A2 A3 (module 2)
}

void loop()
{
  voltage1 = myADC1.readConversion() * LSB_6144;    // corresponding multiplier for +/-6.144V
  voltage2 = myADC2.readConversion() * LSB_4096;    // corresponding multiplier for +/-4.096V
  Serial.print(voltage1);
  Serial.print("\t");
  Serial.println(voltage2);
  delay(500);
}
