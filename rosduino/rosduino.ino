/*
 */

#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/String.h>

#define USB_CON

# define rPWM 7
# define rIn 8
# define rOut 9

# define lPWM 5
# define lIn 2
# define lOut 3

void changeDirection(int in, int out, int pwm, int power){
  int dir = 1;
  if (power < 0) { power = power * -1; dir = -1;}
  if (power > 255) { power = 255;}
  
  
  if (dir > -1){
      digitalWrite(in, HIGH);
      digitalWrite(out, LOW);
    } else {
      digitalWrite(in, LOW);
      digitalWrite(out, HIGH);
    }
    analogWrite(pwm, power);
}
ros::NodeHandle  nh;
//std_msgs::String str_msg;
//ros::Publisher chatter("chatter", &str_msg);
//char hello[13] = "hello world!";

void publish(){
  //str_msg.data = hello;
  //chatter.publish(&str_msg);
}

unsigned long int timer;
void messageCbl (const std_msgs::Int16& msg) {
  int power = msg.data;
  changeDirection(lIn, lOut, lPWM, power);
  //publish();
   }

void messageCbr (const std_msgs::Int16& msg) {
   int power = msg.data;
   changeDirection(rIn, rOut, rPWM, power);
   //publish();
}
   
ros::Subscriber<std_msgs::Int16> subl("leftWheel", &messageCbl);
ros::Subscriber<std_msgs::Int16> subr("rightWheel", &messageCbr);

void setup()
{
  timer = millis();
  nh.initNode();
  nh.subscribe(subl);
  nh.subscribe(subr);
  // nh.advertise(chatter);

  // PIN INITIALIZATION

  pinMode(lIn, OUTPUT);
  pinMode(lOut, OUTPUT);
  pinMode(lPWM, OUTPUT);

  pinMode(rIn, OUTPUT);
  pinMode(rOut, OUTPUT);
  pinMode(rPWM, OUTPUT);
}
void loop(){
  nh.spinOnce();
}

