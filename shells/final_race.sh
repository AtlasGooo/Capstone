#!/bin/bash

###
 # @Author: Lin Zijun
 # @Date: 2021-05-22 19:51:40
 # @LastEditTime: 2021-05-28 20:35:10
 # @LastEditors: Please set LastEditors
 # @Description: In User Settings Edit
 # @FilePath: /myturtlebot3/shells/final_race.sh
### 


# gnome-terminal -- roscore
# sleep 2.0s

### simple image trans
gnome-terminal -- rosrun simple_img_trans simple_img_trans
sleep 1s

### ar track alvar
gnome-terminal -- roslaunch simple_img_trans ar.launch
sleep 0.5s

### sound play node
gnome-terminal -- rosrun sound_play soundplay_node.py
sleep 0.5s

### say node
gnome-terminal -- rosrun final_race say.py
sleep 0.5s


### race system node
gnome-terminal -- rosrun final_race final_race
sleep 1s

