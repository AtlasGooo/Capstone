/*
 * @Author: your name
 * @Date: 2021-05-24 11:57:21
 * @LastEditTime: 2021-05-29 11:05:41
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /myturtlebot3/src/final_race/include/Systools.hpp
 */
#ifndef _SYSDEPENDS_HPP_
#define _SYSDEPENDS_HPP_


#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <mutex>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <math.h>


using namespace std;


/// move_base
#include <move_base/move_base.h>
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <move_base_msgs/MoveBaseActionResult.h>

#include <actionlib/client/simple_action_client.h>

/// amcl
#include <geometry_msgs/PoseWithCovarianceStamped.h>

/// std_msgs String
#include <std_msgs/String.h>

/// MoveManager
#include "MoveManager.hpp"

/// LineDetect
#include "LineDetector.hpp"
#include <geometry_msgs/Twist.h>

// ar track alvar, visualization msgs
#include <visualization_msgs/Marker.h>


/**
 * @brief: To judge if the running mode is 
 */
enum RunMode{
    MODE_BEGIN_ONLY = 0,
    MODE_ACTION_ONLY,
    MODE_COMPLETE
};
enum TaskNames{
    TASK_PS = 0,
    TASK_SS,
    TASK_LINE
};
enum TaskType{
    SERIAL_TASK = 0,
    PARALLEL_TASK
};
struct poseXY_ZW{
    double transX;
    double transY;
    double oriZ;
    double oriW;
};

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MBClient; 


class SysInfo
{
public:
    mutex mu_;
    
public:
    geometry_msgs::PoseWithCovarianceStamped poseStamped;
};


class SysTools
{
public:
    SysTools(SysInfo* sysinfo){this->p_sysinfo = sysinfo;}
    ~SysTools(){}
    
    bool sentActionGoal(int sequence = 0 , double posX = 0.5, double posY = 0.5, \
                                double oriZ = 0.0, double oriW = 0.5  );

    void subscribePose(geometry_msgs::PoseWithCovarianceStamped pose_msg);

    void pubVelCmd(double transX, double oriW);

    poseXY_ZW xy_ang_2_xy_zw(double x, double y, double angle360);

public:
    SysInfo* p_sysinfo;

    ros::NodeHandle nh;

    std::unique_ptr<MBClient> client;
    mutex mu_client_;

    std::unique_ptr<ros::Subscriber> poseSub;  

    ros::Publisher sayPub;      

    ros::Publisher velPub;

    // MoveManager mvManager;

    // image_transport::ImageTransport *it;
    // image_transport::Subscriber imgSub;
    // image_transport::Publisher imgPub;



};



class SysConfig
{
public:
    void readFile(string filePath);

    void showConfig();

public:
    string packagePath;
    string sysConfigFilePath;
    string taskFilePath;
    string lineDetectFilePath;
    string vel_topic;

    int numOfTasks;
    int runMode;

    cv::Mat taskStartPoints;
    cv::Mat taskStartAngles;
    vector<string> taskNames_;
    
    /// left unuse temporarily
    vector<double> speedRatios;    // speed ratio for each class
    
};


#endif