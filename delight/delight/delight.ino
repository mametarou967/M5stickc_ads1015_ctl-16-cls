/*
*******************************************************************************
* Copyright (c) 2023 by M5Stack
*                  Equipped with M5StickC sample source code
*                          配套  M5StickC 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/m5stickc
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/m5stickc
*
* Describe: Button.
* Date: 2021/11/16
*******************************************************************************
*/
#include <M5StickC.h>


unsigned long loopStartTime = 0;

/* After M5StickC is started or reset
  the program in the setUp () function will be run, and this part will only be
  run once. 在 M5StickC
  启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。 */
void setup() {
    M5.begin();  // Initialize the M5StickC object.  初始化 M5StickC 对象
    Serial1.begin(9600,SERIAL_8N1,0,26);
    Wire.begin();  // Init wire and join the I2C network.
    M5.Lcd.setTextColor(
        YELLOW);  // Set the font color to yellow.  设置字体颜色为黄色
    M5.Lcd.setRotation(3);
    
    delay(3000); // 少しだけ画面を表示しておく
    loopStartTime = micros();
}

/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {
  // 1病経過したら、計測して送信する
  if(labs(micros() - loopStartTime) > 60000000) // 1分に一回
  {
    loopStartTime = micros();
    // measureCurrent(); // 電流の測定
    sendCurrent();
  }
}

void sendCurrent()
{
  Serial1.write(0x00); // アドレス上位
  Serial1.write(0x00); // アドレス下位
  Serial1.write(0x01); // チャンネル
  Serial1.write('D'); // コマンド
  Serial1.write(0x01);
  Serial1.write(0x00);
  Serial1.write(0x00);
  Serial1.write("\r\n");

}
