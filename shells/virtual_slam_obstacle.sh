#!/bin/bash

###
 # @Author: Lin Zijun
 # @Date: 2021-04-28 15:55:58
 # @LastEditTime: 2021-05-25 15:57:05
 # @LastEditors: Please set LastEditors
 # @Description: In User Settings Edit
 # @FilePath: /myturtlebot3/shells/lzj_virtual_slam_nav.sh
### 


gnome-terminal -- roslaunch turtlebot3_gazebo turtlebot3_world.launch
sleep 2s

gnome-terminal -- roslaunch turtlebot3_slam turtlebot3_slam.launch
sleep 1.5s

# This file is put in /turtlebot3/turtlebot3_example for convenience
# gnome-terminal -- rosrun turtlebot3_example lzj_turtlebot3_obstacle
# sleep 0.5s

