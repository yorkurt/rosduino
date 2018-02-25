/*
 * 
 */

#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/String.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define USB_CON

# define rCoast 12
# define rPWM 13
# define rForward 14 

# define lCoast 8  
# define lPWM 9
# define lForward 10

Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver();

void changeDirection(int forward, int pwm, int power){
  int dir = 1;
  int dirMod = 0; // direction
  if (power < 0) { power = power * -1; dir = -1;}
  if (power > 255) { power = 255;}
  if (dir > -1){
      dirMod = 0;
    } else {
      dirMod = 4095;
    }
    pwmDriver.setPWM(forward, 0, dirMod);
    pwmDriver.setPWM(pwm, 0, power);
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
  changeDirection(lForward, lPWM, power);
  //publish();
   }

void messageCbr (const std_msgs::Int16& msg) {
   int power = msg.data;
   changeDirection(rForward, rPWM, power);
   //publish();
}
   
ros::Subscriber<std_msgs::Int16> subl("leftWheel", &messageCbl);
ros::Subscriber<std_msgs::Int16> subr("rightWheel", &messageCbr);

void setup()
{
  timer = millis();
  pwmDriver.begin();
  pwmDriver.setPWMFreq(300);
  pwmDriver.setPWM(rCoast, 0, 4095);
  pwmDriver.setPWM(lCoast, 0, 4095);
  nh.initNode();
  nh.subscribe(subl);
  nh.subscribe(subr);
  // nh.advertise(chatter);

  // PIN INITIALIZATION

  pinMode(lForward, OUTPUT);
  pinMode(lCoast, OUTPUT);
  pinMode(lPWM, OUTPUT);

  pinMode(rForward, OUTPUT);
  pinMode(rCoast, OUTPUT);
  pinMode(rPWM, OUTPUT);
}
void loop(){
  nh.spinOnce();
}

