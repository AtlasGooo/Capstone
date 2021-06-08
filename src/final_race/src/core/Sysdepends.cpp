/*
 * @Author: Lin Zijun
 * @Date: 2021-05-25 16:05:58
 * @LastEditTime: 2021-05-28 22:12:48
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /myturtlebot3/src/final_race/src/Sysdepends.cpp
 */


#include "SysDepends.hpp"


/**
 * @description: class SysConfig
 */
void SysConfig::readFile(string filePath)
{
    cv::FileStorage fs(filePath,cv::FileStorage::READ);
    this->packagePath = (string)fs["packagePath"];
    this->sysConfigFilePath = packagePath + (string)fs["sysConfigRelated"];
    this->taskFilePath = packagePath + (string)fs["taskConfigRelated"];
    this->lineDetectFilePath = packagePath + (string)fs["lineDetectRelated"];
    
    fs["vel_topic"] >> this->vel_topic;

    fs["numOfTasks"] >> this->numOfTasks;
    
    this->taskStartPoints = cv::Mat_<double>::zeros(numOfTasks,2);   
    fs["taskStartPoints"] >> this->taskStartPoints;

    this->taskStartAngles = cv::Mat_<double>::zeros(numOfTasks,1);
    fs["taskStartAngles"] >> this->taskStartAngles;

    cv::FileNode taskNameNode = fs["taskNames"];
    cv::FileNodeIterator taskNameIt = taskNameNode.begin(), \
                            taskNameIt_end = taskNameNode.end();
    for(; taskNameIt!=taskNameIt_end; taskNameIt++){
        string temp = (string)*taskNameIt;
        this->taskNames_.push_back(temp);
    }

    fs["RunMode"] >> this->runMode;

}

void SysConfig::showConfig()
{
    cout << endl;
    cout << "Show config: " << endl;
    
    cout << "packagePath: " << this->packagePath << endl;
    cout << "sysConfigFilePath: " << this->sysConfigFilePath << endl;
    cout << "taskFilePath: " << this->taskFilePath << endl;
    cout << "lineDetectFilePath: " << this->taskFilePath << endl;

    cout << "vel_topic: " << this->vel_topic << endl;

    cout << "taskStartPoints: " << endl;
    for(int i=0; i<this->taskStartPoints.rows; i++){
        cout << "( " ;
        for(int j=0; j<this->taskStartPoints.cols; j++){
            cout << this->taskStartPoints.at<double>(i,j) << "  " ;
        }
        cout << " )" << endl;
    }

    cout << "taskStartAnlges: " << endl;
    for(int i=0; i<this->taskStartAngles.rows; i++){
        cout << "( " ;
        for(int j=0; j<this->taskStartAngles.cols; j++){
            cout << this->taskStartAngles.at<double>(i,j) << "  " ;
        }
        cout << " )" << endl;
    }

    cout << "taskNames: " << endl;
    for(int i=0; i<this->taskNames_.size(); i++){
        cout << taskNames_[i] << endl;
    } 

    cout << "RunMode: " << runMode <<endl;



    cout << endl;
}



/**
 * @description: class SysTools
 */
bool SysTools::sentActionGoal(int sequence  , double posX , double posY , \
                                double oriZ , double oriW   ){
    std::lock_guard<std::mutex> lg(this->mu_client_);
                                   
    move_base_msgs::MoveBaseActionGoal goal;
    ros::Time timeStamp = ros::Time::now();
    int seq = sequence;
    goal.header.stamp = timeStamp;
    goal.header.seq = seq;
    goal.goal.target_pose.header.frame_id = "map";
    goal.goal.target_pose.header.seq = seq;
    goal.goal.target_pose.header.stamp = timeStamp;
    goal.goal.target_pose.pose.position.x = posX;
    goal.goal.target_pose.pose.position.y = posY;   
    goal.goal.target_pose.pose.position.z = 0.0;  
    goal.goal.target_pose.pose.orientation.x = 0.0;
    goal.goal.target_pose.pose.orientation.y = 0.0;
    goal.goal.target_pose.pose.orientation.z = oriZ;        
    goal.goal.target_pose.pose.orientation.w = oriW;

    this->client->sendGoal(goal.goal);
    cout << "success send goal" << endl;

    this->client->waitForResult(ros::Duration(70.0));
    bool isSuccess = \
        (this->client->getState() == actionlib::SimpleClientGoalState::SUCCEEDED);
    if(isSuccess){
        cout << "success wait for goal" << endl;
    }
    else{
        cout << "failed wait for goal" << endl;
    }


    ros::Duration(0.5).sleep();
    return isSuccess;
}

void SysTools::subscribePose(geometry_msgs::PoseWithCovarianceStamped pose_msg){
    
    /// Print msg
    cout << "receive pose msg:" << endl;

    cout << "infos: (seq,time) " << "( " << pose_msg.header.seq << ",";
    cout << pose_msg.header.stamp.sec << " )" << endl;

    cout << "pose: (x,y,z) ( " << pose_msg.pose.pose.position.x << ",";
    cout << pose_msg.pose.pose.position.y << ",";
    cout << pose_msg.pose.pose.position.z << " )" << endl;
    
    cout << "orient: (z,w) ( " << pose_msg.pose.pose.orientation.z << ",";
    cout << pose_msg.pose.pose.orientation.w << " )" << endl;
}

void SysTools::pubVelCmd(double transX, double oriW){
    geometry_msgs::Twist vel;
    vel.linear.x = transX;
    vel.angular.z = oriW;
    this->velPub.publish(vel);
}

poseXY_ZW SysTools::xy_ang_2_xy_zw(double x, double y, double angle360){
    poseXY_ZW result;
    result.transX = x;
    result.transY = y;
    double angleRad = angle360 * ( M_PI / 180.0);
    result.oriW = std::cos( (0.5*angleRad) );
    result.oriZ = std::sin( (0.5*angleRad) );

    return result;
}




