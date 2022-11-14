#include <Libraries.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("EN's Varocol and 666Qi track");
  pinMode(2, OUTPUT); // 初始化LED引脚为输出模式
  
  //当按下 IO0 按钮，进入配网模式
  pinMode(0, INPUT);
  attachInterrupt(0, network_config_begin, FALLING); // 设置外部中断

  setup_wifi();
  int_web();
}

void loop(){

}
