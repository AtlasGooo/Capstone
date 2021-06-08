/*
 * @Author: Lin Zijun
 * @Date: 2021-05-26 14:35:03
 * @LastEditTime: 2021-05-28 14:39:44
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /myturtlebot3/src/final_race/src/TaskBase.cpp
 */


#include "TaskBase.hpp"

void TaskBase::begin(){

    cout << "Task: " << taskid_  << endl;
    this->p_action->init(); 
    

    cout << "Task: " << taskid_ << " begin to go to (";
    cout << this->startX <<","<< this->startY << "," << this->startAngle360 << " )"<< endl;
    
    poseXY_ZW pose = p_sysTools_->xy_ang_2_xy_zw(startX,startY,startAngle360);
    
    if( !this->p_sysTools_->sentActionGoal(taskid_,startX,startY,pose.oriZ,pose.oriW) ){
        cout << "Task: " << taskid_ << " failed sent action goal !!!" << endl;
    }

    // if( !this->p_sysTools_->sentActionGoal(taskid_,startX,startY) ){
    //     cout << "Task: " << taskid_ << " failed sent action goal !!!" << endl;
    // }
}

void TaskBase::taskAction(){
    cout << "task : " << taskid_ << " taskAction(): " << endl ;
    this->p_action->execute();
}

void TaskBase::end(){
    cout << "task : " << taskid_ << " end()." << endl;
    this->p_action->end();

    cout << endl;    
}