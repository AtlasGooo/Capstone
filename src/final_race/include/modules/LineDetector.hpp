/*
 * @Author: Lin Zijun
 * @Date: 2021-05-27 19:45:05
 * @LastEditTime: 2021-05-28 13:07:59
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /myturtlebot3/src/final_race/include/modules/LineDetector.hpp
 */

#ifndef _LINEDETECTOR_HPP_
#define _LINEDETECTOR_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <mutex>
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>

using namespace std;



class LineDetector
{
public:
    LineDetector(string configPath);
    ~LineDetector();

    string getTopic();

    void imgCallBack(const sensor_msgs::CompressedImagePtr &img);

    /**
     * @description: 
     * @brief Whole image process. use those private func. 
     * @param {*}
     * @return Bool value if process failed (found no result).
     *           Can use to count and judge if line is end.
     */
    bool process(cv::Mat img);

    double getTransX();

    double getOriW();

    bool getSuccessState();
    
private:

    void readParam();   /// Read param while it was created

    void showParam();

    void getImg(cv::Mat img);

    void reset();

    /**
     * @brief GaussianFilter + mask up + HSV filther
     */
    void preProcess();

    /**
     * @brief Find contour and filter out contour
     */
    bool filterContour();

    /**
     * @brief 
     */
    bool countMoment();

    void resultVel(); 

private:
    string configPath_;
    cv::Mat orig_img_;
    cv::Mat img_;    
    // cv::Mat preProcessed_;
    bool is_success_;

    double vel_w_;

    double c_x_;
    double c_y_;

    /// Params read from config file
    string imgTopic_;

    int HSVLowHigh_[6];

    int filterKernelSize_;
    double filterSigmaX_;
    double maskUp_;
    
    double vel_x_;
    double velW_max_;

    double minAreaRatio_;

    double PcontrolRatio_;


    
    bool enableTest_;
   
};



#endif