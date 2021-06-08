/*
 * @Author: your name
 * @Date: 2021-05-22 20:18:04
 * @LastEditTime: 2021-05-28 21:29:37
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /myturtlebot3/src/final_race/include/Actions.hpp
 */

#ifndef _ACTIONSNAV_HPP_
#define _ACTIONSNAV_HPP_

#include "ActionBase.hpp"


using namespace std;

class ActionPS: public ActionBase
{
public:
    ActionPS(){
        cout << "create ActionPS." << endl;
    }
    ActionPS(SysConfig* config, SysInfo* sys_info, SysTools* sys_tools):
        ActionBase(config, sys_info, sys_tools)
    {
        cout << "create ActionPS." << endl;
    }

    void init() override;

    void execute() override;

    void end() override;
    
};

class ActionSS: public ActionBase
{
public:
    ActionSS(){
        cout << "create ActionSS." << endl;
    }
    ActionSS(SysConfig* config, SysInfo* sys_info, SysTools* sys_tools):
        ActionBase(config, sys_info, sys_tools)
    {
        cout << "create ActionSS." << endl;
    }

    void init() override;

    void execute() override;

    void end() override;

private:
    void arCallBack(visualization_msgs::Marker al_msgs);

private:
    double x_,y_,z_,ox_,oy_,oz_,ow_;
    int id_;
    ros::Time stamp_;
    string frame_id_;

    bool is_ar_empty_;
    bool received_;

};

class ActionLine: public ActionBase
{
public:
    ActionLine(){
        cout << "create ActionLine." << endl;
    } 
    ActionLine(SysConfig* config, SysInfo* sys_info, SysTools* sys_tools):
        ActionBase(config, sys_info, sys_tools)
    {
        cout << "create ActionLine." << endl;
    }

    // void imgCallBack(const sensor_msgs::CompressedImagePtr &img);

    void init() override;

    void execute() override;

    void end() override;
    
private:
    cv::Mat img_;
    
    LineDetector * p_lineDet_; /// Release in end()
    
    ros::Subscriber *p_sub_;
    
};





#endif