/*
 * @Author: your name
 * @Date: 2021-05-24 10:27:45
 * @LastEditTime: 2021-05-26 15:17:26
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /myturtlebot3/src/final_race/include/System.hpp
 */



#ifndef _SYSTEMNAV_HPP_
#define _SYSTEMNAV_HPP_



#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>

#include "SystemBase.hpp"


using namespace std;


class SystemNav: public SystemBase
{
public:
    SystemNav(){}
    SystemNav(SysConfig* const config, SysInfo* sys_info, SysTools* sys_tools):
        SystemBase(config, sys_info, sys_tools)
    {
        cout << "create systemNav." << endl;
        this->initSys();
    }

    void initSys() override;

    void runSys() override;

};





#endif