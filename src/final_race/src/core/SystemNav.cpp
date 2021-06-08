/*
 * @Author: your name
 * @Date: 2021-05-22 20:18:58
 * @LastEditTime: 2021-05-28 12:25:38
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /myturtlebot3/src/final_race/src/System.cpp
 */


#include "SystemNav.hpp"


void SystemNav::initSys(){
    
    cout << endl << "... Init system ... " << endl;
    this->taskNames_ = this->p_sysConfig_->taskNames_;
    for(int i=0; i<this->taskNames_.size(); i++){
        if(this->taskNames_[i] == "PS"){
            cout << "init system: "<< i << " " << this->taskNames_[i] << endl;            
            this->tasks_.emplace_back(new TaskPS(p_sysConfig_,p_sysInfo_,p_sysTool_,i));
        }
        else if(this->taskNames_[i] == "SS"){
            cout << "init system: "<< i << " " << this->taskNames_[i] << endl;            
            this->tasks_.emplace_back(new TaskSS(p_sysConfig_,p_sysInfo_,p_sysTool_,i));            
        }
        else if(this->taskNames_[i] == "Line"){
            cout << "init system: "<< i << " " << this->taskNames_[i] << endl;            
            this->tasks_.emplace_back(new TaskLine(p_sysConfig_,p_sysInfo_,p_sysTool_,i));            
        }
        else{
            cout << "init system: error task name." << endl; 
        }
    }
}

void SystemNav::runSys(){
    
    cout << endl << "... Run system ... " << endl;
    switch (p_sysConfig_->runMode)
    {
    case RunMode::MODE_BEGIN_ONLY :
        {
            for(int i=0; i<this->tasks_.size(); i++){
                tasks_[i]->begin();
                tasks_[i]->end();
            }  
        }
        break;

    case RunMode::MODE_ACTION_ONLY :
        {   
            /// This mode is useless now. Consider abandon it.
            for(int i=0; i<this->tasks_.size(); i++){
                tasks_[i]->begin();                
                tasks_[i]->taskAction();
                tasks_[i]->end();
            }              
        }
        break;

    case RunMode::MODE_COMPLETE :
        {
            for(int i=0; i<this->tasks_.size(); i++){
                tasks_[i]->begin();                
                tasks_[i]->taskAction();
                tasks_[i]->end();
            }              
        }  
        break;
           
    default:
        break;
    }

}
