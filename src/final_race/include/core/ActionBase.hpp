/*
 * @Author: your name
 * @Date: 2021-05-22 20:17:52
 * @LastEditTime: 2021-05-27 16:19:09
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /myturtlebot3/src/final_race/include/ActionBase.hpp
 */

#ifndef _ACTIONBASE_HPP_
#define _ACTIONBASE_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <thread>

#include "SysDepends.hpp"

using namespace std;



class ActionConfig
{
public:
    ActionConfig(){}
    ActionConfig(string filePath);

    void read(string filePath);

};


class ActionBase
{
public:
    ActionBase(){}
    ActionBase(SysConfig* config, SysInfo* sys_info, SysTools* sys_tools){
        this->p_config_ = config;
        this->p_sysInfo_ = sys_info;
        this->p_sysTools_ = sys_tools;        
    }

    virtual void init() = 0;

    virtual void execute() = 0;

    virtual void end() = 0;

protected:
    SysConfig* p_config_;
    SysTools* p_sysTools_;
    SysInfo* p_sysInfo_;
    
    bool isFinished_;     
};



#endif