/*
 * @Author: your name
 * @Date: 2021-05-22 20:16:06
 * @LastEditTime: 2021-05-26 16:00:04
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /myturtlebot3/src/final_race/include/SystemBase.hpp
 */

#ifndef _SYSTEMBASE_HPP_
#define _SYSTEMBASE_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>

#include "TaskBase.hpp"
#include "TasksNav.hpp"

#include "ActionBase.hpp"
#include "ActionsNav.hpp"

#include "SysDepends.hpp"

using namespace std;


/**
 * @brief System base class
 */
class SystemBase
{
public:
    SystemBase(){}
    SystemBase(SysConfig* const config, SysInfo* sys_info, SysTools* sys_tools){
        this->p_sysConfig_ = config;
        this->p_sysInfo_ = sys_info;
        this->p_sysTool_ = sys_tools;
    }

    virtual void initSys() = 0;

    virtual void runSys() = 0;

protected:

    SysTools* p_sysTool_;
    SysInfo* p_sysInfo_;
    SysConfig *p_sysConfig_;

    /// read from those system val above, in initSys()
    vector<TaskBase*> tasks_;
    vector<string> taskNames_;
    int runmode_;    

    /// control from runSys()
    bool startCmd_;





};





#endif