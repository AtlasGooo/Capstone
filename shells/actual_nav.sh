###
 # @Author: your name
 # @Date: 2021-05-26 18:32:31
 # @LastEditTime: 2021-05-28 15:53:52
 # @LastEditors: Please set LastEditors
 # @Description: In User Settings Edit
 # @FilePath: /myturtlebot3/shells/actual_nav.sh
### 


$MAP = "/home/lzj/Workspaces/myturtlebot3/src/final_race/maps/actual_map/map.yaml"
gnome-terminal -- roslaunch final_race lzj_turtlebot3_navigation.launch 
sleep 0.5s