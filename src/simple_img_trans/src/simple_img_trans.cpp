/*
 * @Author: Lin Zijun
 * @Date: 2021-05-28 18:47:30
 * @LastEditTime: 2021-05-28 19:25:04
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /simple_img_trans/src/simple_img_trans.cpp
 */



#include "simple_img_trans.hpp"


ImgTransverser::ImgTransverser(){
  this->init();
}

void ImgTransverser::init(){
}

void ImgTransverser::imgCallBack(const sensor_msgs::CompressedImagePtr &msg){
    cv_bridge::CvImagePtr cv_ptr;
    try{
      cv_ptr = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8);
      this->img_ = cv_ptr->image;
    }
    catch(cv_bridge::Exception &e)
    {
		  ROS_ERROR("Could not convert from ' ' to 'bgr8'.");
    }
}

cv::Mat ImgTransverser::getImg(){
  return this->img_;
}

void ImgTransverser::transverImg(){
    
}



