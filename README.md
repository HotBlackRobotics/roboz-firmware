# PARLOMA Hand ROS Driver

The Driver of the PARLOMA Hand written in C++ for the communication 
between the Hand and ROS, using ROSSerial!

## Build

This system are build using Arduino-Makefile.

## Example Usage

Connect the Arduino hand to the Linux PC Port, get the port (my is `/dev/ttyACM0`).
Then run

```
$ rosrun rosserial_python serial_node.py /dev/ttyACM0
```

In a new shell, send a command to `/right_hand`. For instance, to close the index finger, run.

```
$ rostopic pub /right_hand sensor_msgs/JointState "header:
  seq: 0
  stamp: {secs: 0, nsecs: 0}
  frame_id: ''
name: ['index']
position: [1.0]
velocity: []
effort: []" 
```

