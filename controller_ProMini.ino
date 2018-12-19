#include "Nintendo.h"
/* 使用了Nicohood的库
*/
//定义手柄发送信号
CGamecubeConsole GamecubeConsole(3);      //定义给主机发送信号的针脚为3
Gamecube_Data_t d = defaultGamecubeData;   //要发送到主机的数据的结构

//命令必须，虚构一个手柄针脚在7，并不需要连接一个真实手柄
CGamecubeController GamecubeController1(7);

//定义数据按键的针脚 
const int A = 0;//定义常量针脚
const int B = 1;
const int X = 2;
const int Y = 4;
const int Z = 5;
const int START = 6;
const int R = 8;
const int L = 9;
const int DUP = 10;
const int DDOWN = 14;
const int DLEFT = 15;
const int DRIGHT = 16;

//This is the value of analog shielding 74 is lightest possible on gamecube.  it varies from gamecube to dolphin no idea why..right left是模拟数据，目前不明
//if this does not work on your system or something like that keep raising it by 1 until it works.如果不工作74加1尝试
const int RLIGHTv = 74;
const int RLIGHT = 36; //doesnt exist

//左右摇杆
int X1 = A0;//左摇杆X
int Y1 = A1;//左摇杆Y
int X2 = A2;//右摇杆X
int Y2 = A3;//右摇杆Y
//int LEFT = A3;//左扳机
//int RIGHT = A3;//右扳机

//int CLEFT = 14;//-
//int CRIGHT = 15;//-
//int CUP = 16;//-
//int CDOWN = 17;//-

void setup()
{
  //输入引脚默认为上拉，当同地连接时确认按键动作
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(X, INPUT_PULLUP);
  pinMode(Y, INPUT_PULLUP);
  pinMode(Z, INPUT_PULLUP);
  pinMode(START, INPUT_PULLUP);
  
  pinMode(R, INPUT_PULLUP);
  pinMode(L, INPUT_PULLUP);
  pinMode(RLIGHT, INPUT_PULLUP);

//  pinMode(LEFT, INPUT_PULLUP);
//  pinMode(RIGHT, INPUT_PULLUP);
//  pinMode(UP, INPUT_PULLUP);
//  pinMode(DOWN, INPUT_PULLUP);
  
//  pinMode(X1, INPUT_PULLUP);
//  pinMode(X2, INPUT_PULLUP);
//  pinMode(Y1, INPUT_PULLUP);
//  pinMode(Y2, INPUT_PULLUP);
  
//  pinMode(CLEFT, INPUT_PULLUP);
//  pinMode(CRIGHT, INPUT_PULLUP);
//  pinMode(CUP, INPUT_PULLUP);
//  pinMode(CDOWN, INPUT_PULLUP);

  //This is needed to run the code.
  GamecubeController1.read();
}

void loop()
{
  //This resets and establishes all the values after the controller sends them to the console and helps with initial "zeroing"
  int pinA = 0;
  int pinB = 0;
  int pinX = 0;
  int pinY = 0;
  int pinZ = 0;
  int pinSTART = 0;

  int pinR = 0;
  int pinL = 0;
  int pinRLIGHT = 0;
  
  int pinDUP = 0;
  int pinDDOWN = 0;
  int pinDLEFT = 0;
  int pinDRIGHT = 0;

//  int pinLEFT = 0;
//  int pinRIGHT = 0;
//  int pinUP = 0;
//  int pinDOWN = 0;

//  int pinX1 = 0;
//  int pinX2 = 0;
//  int pinY1 = 0;
//  int pinY2 = 0;

//  int pinCLEFT = 0;
//  int pinCRIGHT = 0;
//  int pinCUP = 0;
//  int pinCDOWN = 0;

//  int pinxAxisC = 128;
//  int pinyAxisC = 128;
  
//  int pinxAxis = 128;
//  int xmod = 0;
//  int pinyAxis = 128;
   
  if (analogRead(X1))pinxAxis = 255; //左摇杆X轴
  if (digitalRead(Y1))pinxAxis = 0; //左摇杆Y轴
  if (digitalRead(X2))pinyAxisC = 255; //右摇杆X轴
  if (digitalRead(Y2))pinyAxisC = 4; //右摇杆Y轴
  
  //Reads CStick pins, same logic as controlstick values.
//  if (digitalRead(CLEFT) == HIGH && digitalRead(CRIGHT) == LOW)pinxAxisC = 255;
//  if (digitalRead(CLEFT) == LOW && digitalRead(CRIGHT) == HIGH)pinyAxisC = 0;
//  if (digitalRead(CDOWN) == HIGH && digitalRead(CUP) == LOW)pinxAxisC = 255;
//  if (digitalRead(CDOWN) == LOW && digitalRead(CUP) == HIGH)pinyAxisC = 0;

  if (digitalRead(A) == LOW)pinA = 1;
  if (digitalRead(B) == LOW)pinB = 1;
  if (digitalRead(X) == LOW)pinX = 1;
  if (digitalRead(Y) == LOW)pinY = 1;
  if (digitalRead(Z) == LOW)pinZ = 1;
  if (digitalRead(START) == LOW)pinSTART = 1;
  if (digitalRead(RLIGHT) == LOW)pinRLIGHT = RLIGHTv;
  if (digitalRead(R) == LOW)pinR = 1;
  if (digitalRead(L) == LOW)pinL = 1;
  if (digitalRead(DUP) == LOW)pinDUP = 1;
  if (digitalRead(DDOWN) == LOW)pinDDOWN = 1;
  if (digitalRead(DLEFT) == LOW)pinDLEFT = 1;
  if (digitalRead(DRIGHT) == LOW)pinDRIGHT = 1;


  //reports data
  d.report.a = pinA;
  d.report.b = pinB;
  d.report.x = pinX;
  d.report.y = pinY;
  d.report.z = pinZ;
  d.report.start = pinSTART;
  d.report.r = pinR;
  d.report.l = pinL;
  d.report.left = pinRLIGHT;
  d.report.dup = pinDUP;
  d.report.ddown = pinDDOWN;
  d.report.dleft = pinDLEFT;
  d.report.dright = pinDRIGHT;
  d.report.xAxis = pinxAxis;
  d.report.yAxis = pinyAxis;
  d.report.cxAxis = pinxAxisC;
  d.report.cyAxis = pinyAxisC;
  //sends the complied data to console when console polls for the input
  GamecubeConsole.write(d);


}
