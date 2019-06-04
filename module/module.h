#define WAIT 32

#define SAMPLING_RATE 280 //sampling rate
#define D_TIME 40 //delta time
#define SLEEP_TIME 9680 //sleep time

#define LED_IR 2 //D2
#define INPUT_DATA 0 //A0

#define DHT_INPUT_DATA 3 //D3
#define DHT_TYPE 11 //using dht11

#define IIC_ADDR 0x23

float float finedust_sensor();
float finedust_sensor_raw();
char dht_hum_mapping(int data);
char dht_temp_mapping(int data);
char dht11_hum_sensor();
char dht11_temp_sensor();
char dht11_hum_sensor_raw();
char dht11_temp_sensor_raw();
void BH1750_sensor_init(int addr);
int BH1750_sensor_read(int addr, byte *buf);
char BH1750_sensor();
char BH1750_sensor_raw();