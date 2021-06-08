###
 # @Author: Lin Zijun
 # @Date: 2021-05-25 17:12:50
 # @LastEditTime: 2021-05-27 09:24:35
 # @LastEditors: Please set LastEditors
 # @Description: In User Settings Edit
 # @FilePath: /myturtlebot3/shells/virtual_nav.sh
### 


gnome-terminal -- roslaunch turtlebot3_gazebo turtlebot3_world.launch
sleep 1.5s

$MAP = "/home/lzj/Workspaces/myturtlebot3/src/final_race/maps/sim_map_fake/sim_map_fake.yaml"
gnome-terminal -- roslaunch final_race lzj_turtlebot3_navigation.launch map_file:=$MAP
sleep 0.5s