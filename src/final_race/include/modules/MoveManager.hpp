/*
 * @Author: your name
 * @Date: 2021-05-24 10:52:38
 * @LastEditTime: 2021-05-24 20:08:35
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /myturtlebot3/src/final_race/include/MoveManager.hpp
 */

#ifndef _MOVEMANAGER_HPP_
#define _MOVEMANAGER_HPP_


#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <mutex>

using namespace std;


/**
 * @description: To control speed. It's a layer between your system and robot moving
 *  controller. Can implement speed control algorithm such as PID controller. 
 *  It's a class that can be included in SysTools.
 * @param {*}
 * @return {*}
 */
class MoveManager
{
public:
    void getTargetVel();

    void computeVel();

    void sendComputedVel();
    
public:
    double vel;
};

#endif

