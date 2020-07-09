  //             循迹模块设置               //
#define track_PIN0 A0
#define track_PIN1 A1
#define track_PIN2 2
#define track_PIN3 A2
#define track_PIN4 A3

float error = 0, P = 0, I = 0, D = 0, PID_value = 0;//pid直道参数 
float previous_error = 0; //误差值 
int sum;
/*循迹模块引脚初始化*/

void setup_xunji()
{ 
  pinMode(track_PIN0,INPUT);
  pinMode(track_PIN1,INPUT);
  pinMode(track_PIN2,INPUT);
  pinMode(track_PIN3,INPUT);
  pinMode(track_PIN4,INPUT);

}
int temp[5];
///////////////////////////////////////////////
void xunji_values()
{
  sensor[0] = analogRead(track_PIN0);//特殊判断位
  sensor[1] = analogRead(track_PIN1);
  sensor[2] = analogRead(track_PIN2);
  sensor[3] = analogRead(track_PIN3);
  sensor[4] = analogRead(track_PIN4);
  
  if(sensor[1] > 300)temp[1] = -4;
  else temp[1] = 0;
  if(sensor[2] > 300)temp[2] = -1;
  else temp[2] = 0;
  if(sensor[3] > 300)temp[3] = 1;
  else temp[3] = 0;
  if(sensor[4] > 300)temp[4] = 4;
  else temp[4] = 0;
  sum=temp[1]+temp[2]+temp[3]+temp[4];
}
/////////////////////////////////////////////
void xunji_pid()
{ 
  error=sum;  
  if(sensor[2]>300&&sensor[3]>300)
    error=0;
  P = error;
  I = I + error;
  D = error - previous_error;
 
  PID_value = (Kp * P) + (Ki * I) + (Kd * D);
 
  previous_error = error;
  left_motor_speed = (int)(initial_motor_speed - PID_value);
  right_motor_speed = (int)(initial_motor_speed + PID_value);
  
  if(error == 0)
  {
    left_motor_speed = initial_motor_speed;
    right_motor_speed = initial_motor_speed;
  }
}
