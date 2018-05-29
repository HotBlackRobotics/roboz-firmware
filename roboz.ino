#include <ros.h>
#include <string.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/UInt16.h>
#include <Servo.h>

ros::NodeHandle nh;

Servo servo;

#define LED_RED 3
#define LED_GREEN 5
#define LED_BLUE 6

void ledWrite(int r, int g, int b){
	analogWrite(LED_RED, 255-r);
	analogWrite(LED_GREEN, 255-g);
	analogWrite(LED_BLUE, 255-b);
}

void getRGB(int hue, int sat, int val, int colors[3]) {
	// hue: 0-259, sat: 0-255, val (lightness): 0-255
	int r, g, b, base;

	if (sat == 0) { // Achromatic color (gray).
		colors[0]=val;
		colors[1]=val;
		colors[2]=val;
	} else  {
		base = ((255 - sat) * val)>>8;
		switch(hue/60) {
			case 0:
				r = val;
				g = (((val-base)*hue)/60)+base;
				b = base;
				break;
			case 1:
				r = (((val-base)*(60-(hue%60)))/60)+base;
				g = val;
				b = base;
				break;
			case 2:
				r = base;
				g = val;
				b = (((val-base)*(hue%60))/60)+base;
				break;
			case 3:
				r = base;
				g = (((val-base)*(60-(hue%60)))/60)+base;
				b = val;
				break;
			case 4:
				r = (((val-base)*(hue%60))/60)+base;
				g = base;
				b = val;
				break;
			case 5:
				r = val;
				g = base;
				b = (((val-base)*(60-(hue%60)))/60)+base;
				break;
		}
		colors[0]=r;
		colors[1]=g;
		colors[2]=b;
	}
}

void setLED(int hue, int l){
	int col[3] = {0,0,0};
	getRGB(hue, 255, l, col);
	ledWrite(col[0], col[1], col[2]);
}




void servo_cb( const std_msgs::UInt8 & msg) {
	int pos = msg.data;
	if (pos > 180) pos = 180;
	if (pos < 0) pos = 0;
	servo.write(pos);
}

void led_cb( const std_msgs::UInt16 & msg) {
	int h = msg.data%260;
    setLED(h, 255);
}


ros::Subscriber<std_msgs::UInt8> sub_servo("servo", &servo_cb );
ros::Subscriber<std_msgs::UInt16> sub_led("led", &led_cb );

int i = 0;
void setup() {
    servo.attach(11);
    nh.initNode();
    nh.subscribe(sub_servo);
    nh.subscribe(sub_led);
	setLED(0, 255);
}

void loop() {
    nh.spinOnce();
	servo.write(i++%180);
	delay(100);
}