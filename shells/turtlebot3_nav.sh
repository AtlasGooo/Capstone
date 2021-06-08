#!/bin/bash
###
 # @Author: Lin Zijun
 # @Date: 2021-04-21 17:48:58
 # @LastEditTime: 2021-05-22 19:50:56
 # @LastEditors: Please set LastEditors
 # @Description: In User Settings Edit
 # @FilePath: /myturtlebot3/shells/turtlebot3_nav.sh
### 



gnome-terminal -- roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:=$HOME/ros_saves/lab5/map/map.yaml
sleep 0.5s