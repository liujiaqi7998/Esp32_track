#include <Arduino.h>
#include <Wire.h>

void sendI2C(uint8_t addr, uint8_t data)
{
  Wire.beginTransmission(addr); // 开始传输
  Wire.write(data);             // 发送数据
  Wire.endTransmission();       // 结束传输
}
void sendI2C(uint8_t addr, uint8_t *data, size_t len)
{
  Wire.beginTransmission(addr); // 开始传输
  Wire.write(data, len);        // 发送数据
  Wire.endTransmission();       // 结束传输
}

void readI2C(uint8_t addr, size_t len)
{
  Wire.requestFrom(addr, len); // 请求数据
  while (Wire.available())
  {                       // 读取数据
    char c = Wire.read(); // 从Wire 上读取一个char
    Serial.print(c);
  }
}

void gyroscope_init()
{
  uint8_t handshake[] = {0x06, 0x01};
  sendI2C(0x68, handshake, 2);
  sendI2C(0x68, 0x06);
  sendI2C(0x68, 0x7F);
}

void setup()
{
  // put your setup code here, to run once:
  Wire.setPins(21, 22);
  Wire.begin();         // join i2cbus (主机，不用写IIC地址)
  Serial.begin(115200); // 串口输出
  gyroscope_init();
}

void loop()
{


  sendI2C(0x68, 0x2D);
  readI2C(0x68, 12);

  delay(100);
}