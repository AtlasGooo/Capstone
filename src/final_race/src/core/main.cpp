/*
 * @Author: your name
 * @Date: 2021-05-22 20:19:04
 * @LastEditTime: 2021-05-28 17:09:15
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /myturtlebot3/src/final_race/src/main.cpp
 */


#include <iostream>
#include <string>
#include <vector>
#include <ros/ros.h>
#include <opencv2/opencv.hpp>

#include "SystemBase.hpp"
#include "SystemNav.hpp"

#include "TaskBase.hpp"
#include "TasksNav.hpp"

#include "ActionBase.hpp"
#include "ActionsNav.hpp"

using namespace std;


/// Additional
#include <move_base/move_base.h>
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <move_base_msgs/MoveBaseActionResult.h>

#include <actionlib/client/simple_action_client.h>

/// amcl
#include <geometry_msgs/PoseWithCovarianceStamped.h>


int main(int argc, char ** argv){

    ros::init(argc, argv, "final_race_node");
    ros::NodeHandle nh;

    /// system config
    string sysConfigPath = "/home/lzj/Workspaces/myturtlebot3/src/final_race/config/sysConfig.yaml";
    SysConfig config;
    config.readFile(sysConfigPath);
    config.showConfig();

    /// system info
    SysInfo sysinfo;

    /// system tools
    SysTools systools(&sysinfo);
    systools.nh = ros::NodeHandle();
    systools.client = std::make_unique<MBClient>("move_base",true);
    while(!systools.client->waitForServer(ros::Duration(3.0))){
        cout << "failed wait for server. try again." << endl;
    }
    systools.poseSub = \
        std::make_unique<ros::Subscriber>\
            (systools.nh.subscribe("/amcl_pose",1,&SysTools::subscribePose,&systools));
    systools.sayPub = systools.nh.advertise<std_msgs::String>("/final_race/say",1);

    // if(false){
    //     systools.velPub = systools.nh.advertise<geometry_msgs::Twist>(config.vel_topic,1);        
    // }
    // systools.velPub = systools.nh.advertise<geometry_msgs::Twist>(config.vel_topic,1);


    /// create system 
    std::unique_ptr<SystemBase> system = \
        std::make_unique<SystemNav>(&config,&sysinfo,&systools);

    system->runSys();


    /// TODO: if you need to receive msg, you should put the spin function in another thread
    ros::Rate loopRate(1);
    while (ros::ok())
    {
        cout << "spinning..." << endl;        
        ros::spinOnce();
        loopRate.sleep();
    }
    

    return 0;
}