/*
 * @Author: your name
 * @Date: 2021-05-22 20:18:12
 * @LastEditTime: 2021-05-27 15:40:30
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /myturtlebot3/src/final_race/include/Tasks.hpp
 */

#ifndef _TASKNAV_HPP_
#define _TASKNAV_HPP_


#include "TaskBase.hpp"



using namespace std;


class TaskPS: public TaskBase
{
public:
    TaskPS():TaskBase()
    {
        cout << "create TaskPS." << endl;
        this->init();
    }
    TaskPS(SysConfig* config, SysInfo* sys_info, SysTools* sys_tools, int taskid=0):
        TaskBase(config, sys_info, sys_tools, taskid)
    {
        this->init();
        cout << "create TaskPS." << endl;
    }

    void init() override;
};

class TaskSS: public TaskBase
{
public:
    TaskSS():TaskBase()
    {
        cout << "create TaskSS." << endl;
        this->init();        
    }
    TaskSS(SysConfig *config, SysInfo* sys_info, SysTools* sys_tools, int taskid=0):
        TaskBase(config, sys_info, sys_tools, taskid)
    {
        cout << "create TaskSS." << endl;
        this->init();
    }

    void init() override; 
};

class TaskLine: public TaskBase
{
public:
    TaskLine():TaskBase()
    {
        cout << "create TaskLine." << endl; 
        this->init();       
    }
    TaskLine(SysConfig* config, SysInfo* sys_info, SysTools* sys_tools, int taskid=0):
        TaskBase(config, sys_info, sys_tools, taskid)
    {
        cout << "create TaskLine." << endl;
        this->init();
    }
    void init() override;
};




#endif