/*
  姓名：宋孝东
  程序开发时间：2024.4.29
  版本号：0.1
  本程序可以实现的功能：控制机械臂实现夹取物品
  本程序的缺点：ESP8266模块没有舵机库，只能手敲代码，看上去代码十分的多
*/
#include <Arduino.h>
#define BLINKER_PRINT Serial
#define BLINKER_WIFI
#define BLINKER_MIOT_LIGHT

#define LEDdeng D5 // 使用语音控制灯开关输出端口

#include <Blinker.h> //使用Blinker库
// 需要修改的代码
char auth[] = "Your Device Secret Key";                    // 点灯科技密钥
char ssid[] = "Your WiFi network SSID or name";            // WIFI名称
char pswd[] = "Your WiFi network WPA password or WEP key"; // WIFI密码

// 软件控制端口——滑块名称
BlinkerSlider Slider1("max_num0");
BlinkerSlider Slider2("max_num1");
BlinkerSlider Slider3("max_num2");
BlinkerSlider Slider4("max_num3");

// 语音控制灯
void miotPowerState(const String &state)
{
  BLINKER_LOG("need set power state: ", state);

  if (state == BLINKER_CMD_ON)
  {
    digitalWrite(LEDdeng, HIGH);

    BlinkerMIOT.powerState("on");
    BlinkerMIOT.print();
  }
  else if (state == BLINKER_CMD_OFF)
  {
    digitalWrite(LEDdeng, LOW);

    BlinkerMIOT.powerState("off");
    BlinkerMIOT.print();
  }
}
// 硬件控制端口
// 第一个舵机
int servopin1 = D1;
void servopulse1(int angle) // PWM型号产生函数
{
  int pulsewidth = (angle * 11) + 500;
  digitalWrite(servopin1, HIGH);
  delayMicroseconds(pulsewidth);
  digitalWrite(servopin1, LOW);
  delayMicroseconds(20000 - pulsewidth);
}
// 第二个舵机
int servopin2 = D2;
void servopulse2(int angle) // PWM型号产生函数
{
  int pulsewidth = (angle * 11) + 500;
  digitalWrite(servopin2, HIGH);
  delayMicroseconds(pulsewidth);
  digitalWrite(servopin2, LOW);
  delayMicroseconds(20000 - pulsewidth);
}
// 第三个舵机
int servopin3 = D3;
void servopulse3(int angle) // PWM型号产生函数
{
  int pulsewidth = (angle * 11) + 500;
  digitalWrite(servopin3, HIGH);
  delayMicroseconds(pulsewidth);
  digitalWrite(servopin3, LOW);
  delayMicroseconds(20000 - pulsewidth);
}
// 第四个舵机
int servopin4 = D4;
void servopulse4(int angle) // PWM型号产生函数
{
  int pulsewidth = (angle * 11) + 500;
  digitalWrite(servopin4, HIGH);
  delayMicroseconds(pulsewidth);
  digitalWrite(servopin4, LOW);
  delayMicroseconds(20000 - pulsewidth);
}
// 应用与板子交互，通信数据
void slider1_callback(int32_t value)
{
  BLINKER_LOG("get slider value: ", value);
  Slider1.color("#1E90FF");
  Slider1.print();
  servopulse1(value);
}
void slider2_callback(int32_t value)
{
  BLINKER_LOG("get slider value: ", value);
  Slider2.color("#1E90FF");
  Slider2.print();
  servopulse2(value);
}

void slider3_callback(int32_t value)
{
  BLINKER_LOG("get slider value: ", value);
  Slider3.color("#1E90FF");
  Slider3.print();
  servopulse3(value);
}

void slider4_callback(int32_t value)
{
  BLINKER_LOG("get slider value: ", value);
  Slider4.color("#1E90FF");
  Slider4.print();
  servopulse4(value);
}

void setup()
{
  Serial.begin(115200);
  BLINKER_DEBUG.stream(Serial);
  Slider1.attach(slider1_callback);
  Slider2.attach(slider2_callback);
  Slider3.attach(slider3_callback);
  Slider4.attach(slider4_callback);
  pinMode(LEDdeng, OUTPUT);                     // 配置LEDdeng口为输出模式
  digitalWrite(LEDdeng, LOW);                   // 让LEDdeng口输出低电平
  BlinkerMIOT.attachPowerState(miotPowerState); // 语音控制回调函数
}

void loop()
{
  Blinker.run();
}