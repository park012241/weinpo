#include <SPI.h>

template<typename T>
T command(byte command, T data) {
    digitalWrite(SS, LOW);
    SPI.transfer(command);
    delay(0.5);
    byte buf[sizeof(T)] = {0,};
    SPI.transfer(buf, sizeof(T));
    digitalWrite(SS, HIGH);

    for (int i = 0; i < sizeof(T); i++) {
        data = data << 8 | buf[i];
    }
    return data;
}

void setup(void) {
    SPI.begin();
    digitalWrite(SS, HIGH); // 슬레이브 선택 해제
    SPI.setClockDivider(SPI_CLOCK_DIV16); // 통신 속도 설정 2/4/8/16/32/64/128
    Serial.begin(9600);
}

void loop(void) {
    char a;
    Serial.println(command(0x06, a));
    delay(0.5);
}
