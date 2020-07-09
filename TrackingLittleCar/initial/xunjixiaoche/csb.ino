#define TRIG 4
#define ECHO 3
int csb_Value;
float csb;
float cm; //距离变量
float temp2; // 
int FILTER_N = 11;     
void setup_csb() 
{
  pinMode(TRIG,OUTPUT); 
  pinMode(ECHO,INPUT);
}
 
int csb_cj() 
{
  digitalWrite(TRIG, LOW); //给Trig发送一个低电平
  delayMicroseconds(2);    //等待 2微妙
  digitalWrite(TRIG,HIGH); //给Trig发送一个高电平
  delayMicroseconds(10);    //等待 10微妙
  digitalWrite(TRIG, LOW); //给Trig发送一个低电平
  
  temp2 = float(pulseIn(ECHO, HIGH)); //存储回波等待时间,
  //pulseIn函数会等待引脚变为HIGH,开始计算时间,再等待变为LOW并停止计时
  //返回脉冲的长度
  
  //声速是:340m/1s 换算成 34000cm / 1000000μs => 34 / 1000
  //因为发送到接收,实际是相同距离走了2回,所以要除以2
  //距离(厘米)  =  (回波时间 * (34 / 1000)) / 2
  //简化后的计算公式为 (回波时间 * 17)/ 1000
  
  cm = (temp2 * 17 )/1000; //把回波时间换算成cm
  return cm;
}

int csb_pid()
{
}
