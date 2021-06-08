/*
 * @Author: your name
 * @Date: 2021-05-22 20:17:46
 * @LastEditTime: 2021-05-28 14:08:41
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /myturtlebot3/src/final_race/include/TaskBase.hpp
 */

#ifndef _TASKBASE_HPP_
#define _TASKBASE_HPP_


#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <thread>

#include "ActionBase.hpp"
#include "ActionsNav.hpp"

#include "SysDepends.hpp"

using namespace std;


class TaskConfig
{
public:
    TaskConfig(){}
    TaskConfig(string filePath, int initialX, int initialY){
        this->taskConfigFilePath = filePath;
        // this->setX(initialX);
        // this->setY(initialY);
    }

    void readFile(string filePath);

    // void setX(double x){this->startX = x;}

    // void setY(double y){this->startY = y;}

public:

    /// Params set by calling functions
    // int startX;
    // int startY;

    /// Params set by reading config file
    string taskConfigFilePath;
    string actionConfigFilePath;    // Read from the task config file
    
};

class TaskBase
{
public:
    TaskBase(int taskid = 0){
        this->taskid_ = taskid; 
    }
    TaskBase(SysConfig* config, SysInfo* sys_info, SysTools* sys_tools, int taskid=0){
        this->p_config_ = config;
        this->p_sysInfo_ = sys_info;
        this->p_sysTools_ = sys_tools;
        this->taskid_ = taskid; 
        this->startX = p_config_->taskStartPoints.at<double>(taskid,0);
        this->startY = p_config_->taskStartPoints.at<double>(taskid,1);
        this->startAngle360 = p_config_->taskStartAngles.at<double>(taskid_,0);
        cout << "TaskBase: "<<taskid<<" (startX,startY) ("<< startX <<"," << startY << ")" <<endl; 
    }

    /** 
     * @brief Set some param and create some obj. For ex, create concrete action type,
     * and set TaskType (parallel/sequence). This is also a factory method, to be rewrite
     * by subclass.
     * @param {*}
     */
    virtual void init() = 0;

    /**
     * @brief Go to the start point of this task
     * @param {*}
     * @return {*}
     */
    void begin(); 

    /**
     * @description: 
     * @brief Call the action obj. Judge first the taskType: if parallel, use thread and 
     * pass the isFinished_ to the thread function.
     * @param {*}
     * @return {*}
     */
    void taskAction(); 

    void end();

    void getFinishState();

    void getTaskType();

protected:
    SysConfig* p_config_;
    SysTools* p_sysTools_;
    SysInfo* p_sysInfo_;

    // ActionBase* p_action_;
    std::unique_ptr<ActionBase> p_action;
    thread taskThread_;
    
    int taskType_;
    int taskid_;
    string taskName_;
    double startX;
    double startY;
    double startAngle360;
    
    bool isFinished_;    
};





#endif