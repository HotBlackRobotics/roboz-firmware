#include <ros.h>
#include <string.h>
#include <std_msgs/UInt8.h>
#include <Servo.h>

ros::NodeHandle nh;

Servo servo;

void servo_cb( const std_msgs::UInt8 & msg) {
    if( msg.data <= 180 && msg.data >= 0) {
        servo.write(msg.data);
    }
}

ros::Subscriber<std_msgs::UInt8> sub("servo", &servo_cb );

void setup() {
    servo.attach(9);
    nh.initNode();
    nh.subscribe(sub);
}

void loop() {
    nh.spinOnce();
}