/*
 * @Author: Lin Zijun
 * @Date: 2021-05-28 19:03:42
 * @LastEditTime: 2021-05-28 20:04:32
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /simple_img_trans/src/main.cpp
 */


#include "simple_img_trans.hpp"

using namespace std;

int main(int argc, char ** argv){

    ros::init(argc,argv,"simple_img_trans");
    ros::NodeHandle nh;

    ImgTransverser imgTrans;

    ros::Subscriber imgSub = nh.subscribe("/raspicam_node/image/compressed",
        1, &ImgTransverser::imgCallBack, &imgTrans);

    image_transport::ImageTransport it(nh);
    image_transport::Publisher imgPub = it.advertise("camera/image",1);

    ROS_INFO("Start transversing image.");

    ros::Rate loop_rate(30);
    while(true){
        ros::spinOnce();
        if(!imgTrans.getImg().empty()){
            sensor_msgs::ImagePtr imgMsg = \
                cv_bridge::CvImage(std_msgs::Header(),"bgr8",imgTrans.getImg()).toImageMsg();
            imgPub.publish(imgMsg);
        }
    }
    
    


    return 0;
}