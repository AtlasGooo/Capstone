/*
 * @Author: Lin Zijun
 * @Date: 2021-05-28 18:50:46
 * @LastEditTime: 2021-05-28 19:28:44
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /simple_img_trans/include/simple_img_trans/simple_img_trans.hpp
 */

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <mutex>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>

using namespace std;






class ImgTransverser
{
public:
    ImgTransverser();

    void init();

    void imgCallBack(const sensor_msgs::CompressedImagePtr &msg);

    void transverImg();

    cv::Mat getImg();
    
private:
    cv::Mat img_;
};