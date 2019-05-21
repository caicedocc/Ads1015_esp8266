/*
  This example shows the effective sampling rate reading
  one single ended ADS1015 analog channel.
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
  DR_128        128 (Samples per second)
  DR_250
  DR_490
  DR_920
  DR_1600       (default)
  DR_2400
  DR_3300       3300 SPS
  ---------- Corresponding multiplier in Volts (V) ---------------
  LSB_6144      +/-6.144V (LSB size)
  LSB_4096      +/-4.096V
  LSB_2048      +/-2.048V
  LSB_1024      +/-1.024V
  LSB_0512      +/-0.512V
  LSB_0256      +/-0.256V
*/

#include <Ads1015_esp8266.h>
Ads1015_esp8266 myADC(0x48);                // slave address pin connected to GND

void setup()
{
  Serial.begin(9600);
  myADC.begin(D2, D1);                      // SDA = D2, SCL = D1 (nodeMCU v1.0)
  myADC.selectInput(MUX_SGL_3);             // analog input A3 single ended
  myADC.selectGain(FSR_4096);               // amplifier scale range +/-4.096V
  myADC.selectRate(DR_3300);                // max sampling rate 3300 SPS
}

void loop()
{
  int result;
  int samples = 0;
  Serial.println("Start reading samples...");
  unsigned long timer = millis();
  while (millis() - timer < 1000)
  {
    result = myADC.readConversion();
    samples++;
  }
  Serial.print("Effective sample rate (SPS)= ");
  Serial.println(samples);
  Serial.print("Last voltage (Volts)= ");
  Serial.println(result * LSB_4096);        // corresponding multiplier for +/-4.096V
  Serial.println();
  delay(1000);
}
