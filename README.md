# Roboz ROS Driver

The Driver of the Roboz project written in C++ for the communication 
between the Robot and ROS, using ROSSerial!

## Build

This system are build using Arduino-Makefile.

## Example Usage

Connect the Arduino hand to the Linux PC Port, get the port (my is `/dev/ttyACM0`).
Then run

```
$ rosrun rosserial_python serial_node.py /dev/ttyACM0
```

Now you'll see two topic to control the robot:

 - `\led` (`std_msgs/UInt8`) controls the eyes' Led Color. The topic value control the Hue of the Color.
 - `\servo` (`std_msgs/UInt8`) controls the mouth position.