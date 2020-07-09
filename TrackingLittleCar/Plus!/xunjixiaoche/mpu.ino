
void setup_mpu() 
{
  Wire.begin();             //加入 IIC 总线
  Mpu6050.initialize();     //初始化MPU6050
}

void mpu() 
{
  Mpu6050.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);  //获取MPU6050陀螺仪和加速度计的数据
  KalFilter.Angletest(ax, ay, az, gx, gy, gz, dt, Q_angle, Q_gryo, R_angle, C_0, K1);          //通过卡尔曼滤波获取角度
  Gryo = -gz/131; //z轴角速度计算
  Angle1+=Gryo/1000;
  Angle=Angle1*4;//Z轴角度计算
}

void mpu_pd() //无循迹的方向控制
{
  if (Angle<45)
    motor( 50, -50 );
  else if (Angle>55)
    motor( -50 , 50 );
  else
    motor( 0 , 0 );
}

void mpu_pd2(int Angle0)
{
  if (Angle<Angle0-5)
    left_motor_speed = left_motor_speed+20,
    right_motor_speed = right_motor_speed-20;
  else if (Angle>Angle0+10)
      left_motor_speed = left_motor_speed-20,
      right_motor_speed = right_motor_speed+20;
  else
    left_motor_speed = left_motor_speed,
    right_motor_speed = right_motor_speed;
}
