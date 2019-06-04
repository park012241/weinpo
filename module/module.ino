#include "module.h"
#include <SPI.h>
#include <math.h>

void setup(void) {
    pinMode(MISO, OUTPUT);
    pinMode(MOSI, INPUT);
    pinMode(SCK, INPUT); // 마스터에서 클럭을 쏴주는거니 당연히 Input
    pinMode(SS, INPUT);

    SPCR |= _BV(SPE);
    SPCR &= ~_BV(MSTR);
    SPCR |= _BV(SPIE);

    SPI.setClockDivider(SPI_CLOCK_DIV16); // 마스터와 같은 속도로 설정

    Serial.begin(9600);
}

int B = 0;

//ISR (SPI_STC_vect) {// SPI Interrupt / 데이터 수신시 자동 호출
//        // SPDR; // SPDR이라는 8비트 레지스터에 데이터를 수신
////        if (Confirm == 0)
////        Serial.println("무슨 데이터가 넘어왔는지까지 확인이 가능합니다.");
//        if (SPDR==0){
//            return;
//        }
//        Serial.println(SPDR);
//        float t2;
//        float v2;
//        switch (SPDR){
//            case 0x01:
//                SPDR = (uint16_t) 0;
//            break;
//
//            case 0x02:
//                SPDR = (uint32_t) dht11_temp_sensor_raw();
//            break;
//            case 0x03:
//                SPDR = (uint32_t) dht11_hum_sensor_raw();
//            break;
//            case 0x04:
//                SPDR = (uint32_t) BH1750_sensor_raw();
//            break;
//            case 0x05:
//                SPDR = (float) finedust_sensor_raw();
//            break;
//
//            case 0x06:
//                SPDR = (char) dht11_temp_sensor();
//            break;
//            case 0x07:
//                SPDR = (char) dht11_hum_sensor();
//            break;
//            case 0x08:
//                SPDR = (uint16_t) BH1750_sensor();
//            break;
//            case 0x09:
//                SPDR = (float) finedust_sensor();
//            break;
//
//            case 0x10:
//                t2 = dht11_temp_sensor();
//            v2 = dht11_hum_sensor();
//            SPDR = (char) ((9 / 5 * t2) - (0.55 * (1 - v2 / 100) * (9 / 5 * t2 - 26)) + 32);
//            break;
//
//            case 0x11:
//                t2 = powf(1.054, dht11_temp_sensor());
//            v2 = dht11_hum_sensor();
//            SPDR = (char) (v2 - 65) / 14 * t2;
//            break;
//
//            case 0x12:
//                t2 = (9.0 / 5.0) * (dht11_temp_sensor()) + 32;
//            v2 = dht11_hum_sensor();
//            SPDR = (char) (-42.379 + (2.04901523 * t2) + (10.14333127 * v2) - (0.22475541 * t2 * v2) -
//                           (0.00683783 * t2 * t2) - (0.05481717 * v2 * v2) + (0.00122874 * t2 * t2 * v2) +
//                           (0.00085282 * t2 * v2 * v2) - (0.00000199 * t2 * t2 * v2 * v2));
//            break;
//        }
//
//        SPDR = B; // 송신 또한 SPDR을 통해 송신
//}

ISR (SPI_STC_vect) // SPI Interrupt / 데이터 수신시 자동 호출
        {
                byte Confirm = SPDR; // SPDR이라는 8비트 레지스터에 데이터를 수신
        if(Confirm = 0)
        Serial.println("무슨 데이터가 넘어왔는지까지 확인이 가능합니다.");

        SPDR = B; // 송신 또한 SPDR을 통해 송신
        }

void loop(void) {
    B++;
    delay(1000);
}