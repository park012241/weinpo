#include "module.h"
#include "MegunoLink/MegunoLink.h"
#include "MegunoLink/Filter.h"
#include "DHT11/DHT.h"
#include <Wire.h>
#include <math.h>

#define WAIT 32

#define SAMPLING_RATE 280 //sampling rate
#define D_TIME 40 //delta time
#define SLEEP_TIME 9680 //sleep time

#define LED_IR 2 //D2
#define INPUT_DATA 0 //A0

#define DHT_INPUT_DATA 3 //D3
#define DHT_TYPE 11 //using dht11

#define IIC_ADDR 0x23

float finedust_sensor(){
  int count = 0;
  float rawData = 0, calcVoltage = 0, sensValue = 0;
  float filtedData = 0; 
    
  ExponentialFilter<long> ADCFilter(3, 0); //filter setting (weight value: 3) 
  pinMode(LED_IR, OUTPUT);  

  while(count < WAIT){  
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

    delay(100);
  }

  return sensValue;
}

float finedust_sensor_raw(){
  int count = 0;
  float rawData = 0, calcVoltage = 0;
  float filtedData = 0; 
    
  ExponentialFilter<long> ADCFilter(3, 0); //filter setting (weight value: 3) 
  pinMode(LED_IR, OUTPUT);  

  while(count < WAIT){  
    digitalWrite(LED_IR, LOW);
      delayMicroseconds(SAMPLING_RATE);

    rawData = analogRead(INPUT_DATA); 
  
    delayMicroseconds(D_TIME);
    digitalWrite(LED_IR, HIGH);
    delayMicroseconds(SLEEP_TIME);
  
    ADCFilter.Filter(rawData);
    filtedData = ADCFilter.Current();
  
    calcVoltage = filtedData * (5.0 / 1024.0);
    delay(100);
  }

  return calcVoltage;
}

char dht_hum_mapping(int data){
  char val = 0;
  
  if(data <= 20){
    val = 1;  
  }
  else if(data > 20 && data <= 40){
    val = 2;
  }
  else if(data > 40 && data <= 60){
    val = 3;
  }
  else if(data > 60 && data <= 80){
    val = 4;
  }
  else if(data > 80 && data <= 100){
    val = 5;
  }

  return val;
}

char dht_temp_mapping(int data){
  char val = 0;
  
  if(data <= 10){
    val = 1;  
  }
  else if(data > 10 && data <= 20){
    val = 2;
  }
  else if(data > 20 && data <= 30){
    val = 3;
  }
  else if(data > 30 && data <= 40){
    val = 4;
  }
  else if(data > 40 && data <= 50){
    val = 5;
  }

  return val;
}

char dht11_hum_sensor(){
  int hum = 0, filted_hum = 0;  
  int count = 0, val = 0; 

  DHT dht(DHT_INPUT_DATA, DHT_TYPE);
  ExponentialFilter<long> ADCFilter(3, 0); //filter setting (weight value: 3)
  
  while(count < WAIT){
    hum = dht.readHumidity();
    ADCFilter.Filter(hum);
    filted_hum = ADCFilter.Current();
    
    delay(100);
  }

  val = dht_hum_mapping(filted_hum);
  return (char)val; 
}

char dht11_temp_sensor(){
  int temp = 0, filted_temp = 0;
  int count = 0, val = 0;

  DHT dht(DHT_INPUT_DATA, DHT_TYPE);
  ExponentialFilter<long> ADCFilter(3, 0); //filter setting (weight value: 3)

  while(count < WAIT){
    temp = dht.readTemperature();
    ADCFilter.Filter(temp);
    filted_temp = ADCFilter.Current();

    delay(100);
  }

  val = dht_temp_mapping(filted_temp);
  return (char)val;
}

char dht11_hum_sensor_raw(){
  int hum = 0, filted_hum = 0;  
  int count = 0, val = 0; 

  DHT dht(DHT_INPUT_DATA, DHT_TYPE);
  ExponentialFilter<long> ADCFilter(3, 0); //filter setting (weight value: 3)
  
  while(count < WAIT){
    hum = dht.readHumidity();
    ADCFilter.Filter(hum);
    filted_hum = ADCFilter.Current();

    delay(100);
  }

  return (char)filted_hum;
}

char dht11_temp_sensor_raw(){
  int temp = 0, filted_temp = 0;
  int count = 0, val = 0;

  DHT dht(DHT_INPUT_DATA, DHT_TYPE);
  ExponentialFilter<long> ADCFilter(3, 0); //filter setting (weight value: 3)

  while(count < WAIT){
    temp = dht.readTemperature();
    ADCFilter.Filter(temp);
    filted_temp = ADCFilter.Current();
  
    delay(100);
  }

  return (char)filted_temp;
}

void BH1750_sensor_init(int addr){
  Wire.beginTransmission(addr);
  Wire.write(0x10);
  Wire.endTransmission();
}

int BH1750_sensor_read(int addr, byte *buf){
  int i = 0;

  Wire.beginTransmission(addr);
  Wire.requestFrom(addr, 2);  
  
  while(Wire.available()){
    buf[i] = Wire.read();
    i++;
  }

  Wire.endTransmission();
  return i;
}

char BH1750_sensor(){
  int count = 0;
  byte buf[2];
  uint16_t val = 0, filted_val = 0;
  
  ExponentialFilter<long> ADCFilter(3, 0); //filter setting (weight value: 3)
  Wire.begin();
  
  BH1705_sensor_init(IIC_ADDR);
  delay(200);

  while(count < WAIT){
    if(2 == BH1750_sensor_read(IIC_ADDR, buf)){
      val = ((buf[0] << 8) | buf[1]) / 1.2;
      ADCFilter.Filter(val);
      filted_val = ADCFilter.Current(); 
    }
    
    delay(100);
  }

  return (char)filted_val;
} 

char BH1750_sensor_raw(){
  int count = 0;
  byte buf[2];
  uint16_t val = 0, filted_val = 0;
  
  ExponentialFilter<long> ADCFilter(3, 0); //filter setting (weight value: 3)
  Wire.begin();
  
  BH1705_sensor_init(IIC_ADDR);
  delay(200);

  while(count < WAIT){
    if(2 == BH1750_sensor_read(IIC_ADDR, buf)){
      val = ((buf[0] << 8) | buf[1]);
      ADCFilter.Filter(val);
      filted_val = ADCFilter.Current(); 
    }
    
    delay(100);
  }

  return (char)filted_val;
} 