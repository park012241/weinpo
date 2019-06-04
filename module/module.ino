#include "MegunoLink.h"
#include "Filter.h"

#define SAMPLING_RATE 280 //sampling rate
#define D_TIME 40 //delta time
#define SLEEP_TIME 9680 //sleep time

#define LED_IR 2 //D2
#define INPUT_DATA 0 //A0

float rawData = 0, calcVoltage = 0, sensValue = 0;
float filtedData = 0;

ExponentialFilter<long> ADCFilter(5, 0); //filter setting (weight value: 5)

void setup() {
  pinMode(LED_IR, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED_IR, LOW);
  delayMicroseconds(SAMPLING_RATE);

  rawData = analogRead(INPUT_DATA); 
  
  delayMicroseconds(D_TIME);
  digitalWrite(LED_IR, HIGH);
  delayMicroseconds(SLEEP_TIME);
  
  ADCFilter.Filter(rawData);
  filtedData = ADCFilter.Current();

  
  
  calcVoltage = filtedData * (5.0 / 1024.0);
  sensValue = 0.17 * calcVoltage - 0.1;

  Serial.print(sensValue); //debug
  Serial.println("ug/m^3"); //debug
  
  delay(100);
}
