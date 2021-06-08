/*
 * @Author: your name
 * @Date: 2021-05-22 20:18:47
 * @LastEditTime: 2021-05-27 15:31:24
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /myturtlebot3/src/final_race/src/Tasks.cpp
 */


#include "TasksNav.hpp"


void TaskPS::init(){
    this->p_action = std::make_unique<ActionPS>(p_config_,p_sysInfo_,p_sysTools_);
}

void TaskSS::init(){
    this->p_action = std::make_unique<ActionSS>(p_config_,p_sysInfo_,p_sysTools_);   
}

void TaskLine::init(){
    this->p_action = std::make_unique<ActionLine>(p_config_,p_sysInfo_,p_sysTools_);    
}