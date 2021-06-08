/*
 * @Author: your name
 * @Date: 2021-05-22 20:18:40
 * @LastEditTime: 2021-05-29 11:08:02
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /myturtlebot3/src/final_race/src/Actions.cpp
 */


#include "ActionsNav.hpp"


/**
 * @description: ActionPS
 */
void ActionPS::init(){
    cout << "ActionPS::init()" << endl;
}

void ActionPS::execute(){
    cout << "ActionPS::execute()" << endl;

    /// TODO: Add some ops, such as adjust pose through ladar

    std_msgs::String msg;
    msg.data = "stop here";
    p_sysTools_->sayPub.publish(msg);
    ros::Duration(1.0).sleep();
    
}

void ActionPS::end(){
    cout << "ActionPS::end() " << endl;
}

/**
 * @description: ActionSS
 */
void ActionSS::init(){
    cout << "ActionSS::init()" << endl;
}

void ActionSS::execute(){
    cout << "ActionSS::execute()" << endl; 

    ros::Subscriber alvarSub = \
        p_sysTools_->nh.subscribe<visualization_msgs::Marker>("/visualization_marker",1,&ActionSS::arCallBack,this);

    ros::Time t0 = ros::Time::now();
    double sec0 = t0.toSec();

    received_ = false;
    ros::Rate loop_rate(5);
    while(!received_){
        ros::spinOnce();
        ros::Time t1 = ros::Time::now();
        double sec1 = t1.toSec();
        if((sec1 - sec0) > 6){
            break;
        }
    }

}

void ActionSS::end(){
    cout << "ActionSS::end() " << endl;
}

void ActionSS::arCallBack(visualization_msgs::Marker al_msgs){

    ROS_INFO("Receive ar msg !!!!!");
    
    id_ = al_msgs.id;   

    if(id_ != 255 && id_ != -1){
        x_ = \
            al_msgs.pose.position.x;
        y_ = \
            al_msgs.pose.position.y;
        z_ = \
            al_msgs.pose.position.z;
        ox_ = \
            al_msgs.pose.orientation.x;
        oy_ = \
            al_msgs.pose.orientation.y;
        oz_ = \
            al_msgs.pose.orientation.z;
        ow_ = \
            al_msgs.pose.orientation.w; 

        is_ar_empty_ = false;

        received_ = true;

        std_msgs::String msg;
        msg.data = "the number is" + to_string(id_);
        p_sysTools_->sayPub.publish(msg);
    }
    else{
        is_ar_empty_ = true;
    }

}

/**
 * @description: ActionLine
 */

void ActionLine::init(){
    cout << "ActionLine::init()" << endl;
    
    // p_lineDet_ = new LineDetector(p_config_->lineDetectFilePath);

    // *p_sub_ = \
    //     p_sysTools_->nh.subscribe(p_lineDet_->getTopic(), 1, &LineDetector::imgCallBack,p_lineDet_);
}

void ActionLine::execute(){
    cout << "ActionLine::execute()" << endl;


    // bool is_start = false, is_end = false, is_success;
    // int count_success = 0 , count_failed = 0 ;

    // while(true){
    //     ros::spinOnce();
    //     if(!is_start){
    //         /// Havent start yet
    //         if(p_lineDet_->getSuccessState()){
    //             count_success++;
    //             if(count_success > 10)
    //                 is_start = true;
    //         }
    //     }
    //     else{
    //         /// Already start 
    //         if(p_lineDet_->getSuccessState()){
    //             double x = p_lineDet_->getTransX(), w = p_lineDet_->getOriW();
    //             p_sysTools_->pubVelCmd(x,w);
    //         }
    //         else{
    //             count_failed++;
    //             if(count_failed > 20)
    //                 is_end = true;
    //         }
    //     }
        
    //     if(is_end)
    //         break;
        
    // }



}

void ActionLine::end(){
    cout << "ActionLine::end() " << endl;
    // delete p_sub_;
    // delete p_lineDet_;    
}