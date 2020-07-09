#define PWMA 5
#define AIN2 6
#define AIN1 7
#define STBY 8
#define BIN1 9
#define BIN2 10
#define PWMB 11

void setup_motor() 
{
  pinMode(PWMB,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(STBY,OUTPUT);
}


void motor(int speed_left, int speed_right)
{
  digitalWrite(STBY,HIGH);
  if(speed_left>0)
      analogWrite(PWMA, speed_left),
      digitalWrite(AIN2,HIGH),digitalWrite(AIN1,LOW);
  else if(speed_left<0) 
      analogWrite(PWMA, -speed_left),
      digitalWrite(AIN1, HIGH), digitalWrite(AIN2, LOW);
   else
      digitalWrite(AIN1, LOW), digitalWrite(AIN2, LOW);

   if (speed_right > 0)
      analogWrite(PWMB, speed_right),
      digitalWrite(BIN2,HIGH),digitalWrite(BIN1, LOW); 
    else if (speed_right < 0) 
      analogWrite(PWMB, -speed_right),
      digitalWrite(BIN1,HIGH),digitalWrite(BIN2, LOW);
    else
    digitalWrite(BIN1,LOW),digitalWrite(BIN2, LOW);
}
