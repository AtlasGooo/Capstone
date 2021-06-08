#!/bin/bash

###
 # @Author: Lin Zijun
 # @Date: 2021-04-28 15:55:58
 # @LastEditTime: 2021-05-26 19:30:28
 # @LastEditors: Please set LastEditors
 # @Description: In User Settings Edit
 # @FilePath: /myturtlebot3/shells/lzj_virtual_slam_nav.sh
### 




gnome-terminal -- roslaunch final_race lzj_turtlebot3_slam.launch
sleep 1.5s

# gnome-terminal -- rosrun turtlebot3_example lzj_turtlebot3_obstacle
# sleep 0.5s

