
# BehaviorTree.ROS

[BehaviorTree.CPP](https://github.com/BehaviorTree/BehaviorTree.CPP) is a __middleware independent__ framework 
to develop Behavior Trees in C++.
## Overview
The library is not particularly opinionated about the way Actions and Conditions should be created; this gives
more freedom to the developer, but can also be confusing for those people which are getting started with it.

Consequently, many people in the [ROS](http://www.ros.org) community asked for examples and guidelines;
this repository try to provide some basic examples.

Currently, two wrappers are provided:

- [RosServiceNode](include/behaviortree_ros/bt_service_node.h), which can be used to call
  [ROS Services](http://wiki.ros.org/Services)

- [RosActionNode](include/behaviortree_ros/bt_action_node.h) that, similarly, is a wrapper around
  [actionlib::SimpleActionClient](http://wiki.ros.org/actionlib).

## GUI
As of the time of this writing, the [BehaviorTree.CPP](https://github.com/BehaviorTree/BehaviorTree.CPP)'s GUI tool, [Groot](https://github.com/BehaviorTree/Groot), is not explicitly compatible with the ROS library. What this means is that a small number of modifications may need to be made in order for the xml from Groot to be compatible with the ROS tool. 

Once Groot is installed, you can create a new Action node in the GUI or directly in the xml:

        <Action ID="moveTwist">
            <input_port default="0" name="angular_x"/>
            <input_port default="0" name="angular_y"/>
            <input_port default="0" name="angular_z"/>
            <input_port default="0" name="linear_x"/>
            <input_port default="0" name="linear_y"/>
            <input_port default="0" name="linear_z"/>
        </Action>

![Screenshot from 2021-04-12 16-46-59](https://user-images.githubusercontent.com/7253338/114459728-e5fb5280-9bae-11eb-8755-e7547f01d708.png)

