#include <PinChangeInt.h>         //外部中断
#include <FlexiTimer2.h>        //定时中断
#include <KalmanFilter.h>    //卡尔曼滤波
#include "I2Cdev.h"        
#include "MPU6050_6Axis_MotionApps20.h"//MPU6050库文件
#include "Wire.h"   

//***************下面是mpu相关变量***************//
MPU6050 Mpu6050; //实例化一个 MPU6050 对象，对象名称为 Mpu6050
KalmanFilter KalFilter;//实例化一个卡尔曼滤波器对象，对象名称为 KalFilter
int16_t ax, ay, az, gx, gy, gz;  //MPU6050的三轴加速度和三轴陀螺仪数据
float Angle1,Angle=0, Gryo;  //用于显示的角度和临时变量
//***************下面是卡尔曼滤波相关变量***************/

float K1 = 0.05; // 对加速度计取值的权重
float Q_angle = 0.001, Q_gryo = 0.005;
float R_angle = 0.5 , C_0 = 1;
float dt = 0.005; //注意：dt的取值为滤波器采样时间 5ms

int initial_motor_speed = 80 ;      //初始速度 
float Kp = 10,Ki = 0.01, Kd = 1;//pid弯道参数参数
int left_motor_speed, right_motor_speed;

int adc_csb;     //超声波参数
int jishu = 0;
int distance = 50; //与木板的距离

int sensor[5] = {0, 0, 0, 0, 0};                    //5个传感器数值的数组
extern float error,previous_error;

void setup()
{
  Serial.begin(115200); //电机、声音串口波特率115200
  setup_mpu();
  setup_motor();
  setup_xunji();
  setup_csb(); 
}

void loop()
{
  xunji_values(); //获取循迹数据
  if(jishu<5)
    {
     xunji_pid();   //分析循迹数据
     if(sensor[0]>400)
      {
        jishu++;
        delay(500);
      }
     else
      motor(left_motor_speed, right_motor_speed);//输出电机的数据
    }
  else 
    {  
      if(Angle<40||Angle>55)
      {
        mpu();//获取mpu数据
        mpu_pd();
      }
      else if(Angle>40&&Angle<55)
      {
        adc_csb=csb_cj();
//        csb_pid();
        csb_();
//        mpu_pd2(45);
        motor( left_motor_speed , right_motor_speed );
      }
    }
  Serial.print(sensor[0]); 
  Serial.print("//");
  Serial.print(sensor[1]); 
   Serial.print("//");
  Serial.print(sensor[2]); 
   Serial.print("//");
  Serial.print(sensor[3]); 
   Serial.print("//");
  Serial.print(sensor[4]); 
//  Serial.print("\n");
//  Serial.print(cm); 
//  Serial.print("\n");
//  Serial.print(adc_csb); 
//  Serial.print("\n");
//Serial.print(adc_csb);
//Serial.print("\n");
//Serial.print(Angle);
Serial.print("\n");
// Serial.println(1);
} 
