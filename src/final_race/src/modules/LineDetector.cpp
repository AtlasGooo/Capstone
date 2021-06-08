/*
 * @Author: Lin Zijun
 * @Date: 2021-05-27 19:43:16
 * @LastEditTime: 2021-05-28 11:50:20
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /myturtlebot3/src/final_race/src/modules/LineDetecter.cpp
 */

#include "LineDetector.hpp"


/**
 * @description: public 
 */
LineDetector::LineDetector(string configPath){
    cout << "Create LineDetector. " << endl;
    this->configPath_ = configPath;
    this->readParam();
    this->showParam();
    this->is_success_ = false;
}

LineDetector::~LineDetector(){
    cout << "Kill LineDetector. " << endl;
}

string LineDetector::getTopic(){
    return this->imgTopic_;
}

/// TODO: this funtion had not been tested yet
void LineDetector::imgCallBack(const sensor_msgs::CompressedImagePtr &img){
    cv_bridge::CvImagePtr cv_ptr;
	try
	{
		cv_ptr = cv_bridge::toCvCopy(img, sensor_msgs::image_encodings::BGR8);
		cv::Mat tempImg = cv_ptr->image;
        this->is_success_ = this->process(tempImg);
		cv::waitKey(1);
	}
	catch (cv_bridge::Exception &e)
	{
		ROS_ERROR("Could not convert from ' ' to 'bgr8'.");
	}
}

bool LineDetector::process(cv::Mat img){
    this->reset();
    this->getImg(img);
    this->preProcess();
    is_success_ = this->filterContour();
    if(!is_success_){
        return is_success_;
    }
    is_success_ = this->countMoment();
    if(!is_success_){
        return is_success_;
    }
    this->resultVel();

}

double LineDetector::getTransX(){
    return this->vel_x_;
}

double LineDetector::getOriW(){
    return this->vel_w_;
}

bool LineDetector::getSuccessState(){
    return this->is_success_;
}

/**
 * @description: private
 */
void LineDetector::readParam(){

    cout << "LineDetector: reading param ... " << endl;
    cv::FileStorage fs(configPath_,cv::FileStorage::READ);

    fs["imgTopic"] >> this->imgTopic_;
    
    cv::FileNode fn_hsv = fs["HSVLowHigh"];
    cv::FileNodeIterator it_hsv = fn_hsv.begin(), it_hsv_end = fn_hsv.end();
    for(int i=0 ; it_hsv != it_hsv_end; it_hsv++,i++){
        HSVLowHigh_[i] = (int)*it_hsv;
    }

    fs["filterKernelSize"] >> this->filterKernelSize_;
    fs["filterSigmaX"] >> this->filterSigmaX_;
    fs["maskUp"] >> this->maskUp_;
    fs["minAreaRatio"] >> this->minAreaRatio_;
    fs["PcontrolRatio"] >> this->PcontrolRatio_;
    fs["velX"] >> this->vel_x_;
    fs["velW_max"] >> this->velW_max_;

    fs["enableTest"] >> this->enableTest_;
}

void LineDetector::showParam(){
    cout << "LineDetector: show param ... " << endl;

    cout << "imgTopic: " << imgTopic_ << endl;

    cout << "HSVLowHigh: [ ";
    for(int i=0; i<6; i++){
        cout << HSVLowHigh_[i] << "  ";
    }
    cout << " ]" << endl;

    cout << "filterKernelSize: " << filterKernelSize_ << endl;
    cout << "filterSigmaX: " << filterSigmaX_ << endl;  
    cout << "maskUp: " << maskUp_ << endl;     
    cout << "minAreaRatio: " << minAreaRatio_ << endl;
    cout << "PcontrolRatio: " << PcontrolRatio_ << endl;
    cout << "velX: " << vel_x_ << endl;
    cout << "velW_max: " << velW_max_ << endl;

    cout << "enableTest: " << enableTest_ << endl;    
}

void LineDetector::reset(){
    this->is_success_ = true;
}

void LineDetector::getImg(cv::Mat img){
    img_ = img.clone();
    orig_img_ = img.clone();
}



/// TODO: Functions below haven't been test yet. 2021/05/27.

void LineDetector::preProcess(){

    /// Gaussian blur
    int kernelSz = filterKernelSize_;
    double sigmaX = filterSigmaX_;
    cv::GaussianBlur(img_,img_,cv::Size(kernelSz,kernelSz),sigmaX);

    /// Mask up
    int width = img_.cols, height = img_.rows;
    img_( cv::Rect(0,0,width,height*maskUp_) ) = 0;

    /// HSV filter
    cv::Scalar blackLow,blackHigh;
    for(int i=0; i<3; i++){
        blackLow[i] = HSVLowHigh_[i];
        blackHigh[i] = HSVLowHigh_[i+3];
    }
    cv::inRange(img_,blackLow,blackHigh,img_);



    if(enableTest_){
        cv::imshow("preprocessed img", img_);
    }

}

bool LineDetector::filterContour(){
    
    /// Find contours
    vector< vector<cv::Point> > contours;
    vector < cv::Vec4i > hieracy;
    cv::findContours(img_,contours,hieracy,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
    if(contours.empty()){
        cout << "LineDetector: empty contours. " << endl;
        is_success_ = false;
        return is_success_;
    }
    
    /// Count contours areas
    vector<double> areas;
    double area;
    for(int i=0; i<contours.size(); i++){
        area = cv::contourArea(contours[i]);
        areas.push_back(area);
    }

    /// Filter out small area
    double minArea = img_.cols * img_.rows * (1-maskUp_) * minAreaRatio_;
    for(int i=0; i<areas.size(); i++){
        if(areas[i] < minArea){
            cv::drawContours(img_,contours,i,cv::Scalar(0,0,0),-1);
        }
    }
    if(cv::countNonZero(img_) == 0){
        cout << "LineDetector: no big enough area." << endl;
        is_success_ = false;
        return is_success_;
    }


    if(enableTest_){
        cv::imshow("after filter contours",img_);
        cv::waitKey(1);
    }

}

bool LineDetector::countMoment(){
    cv::Moments moment= cv::moments(img_,true);
    c_x_ = moment.m10 / moment.m00;
    c_y_ = moment.m01 / moment.m00;

}

void LineDetector::resultVel(){
    double bias = ( 0.5*img_.cols - c_y_ ) / (double)img_.cols;
    double bias_w = PcontrolRatio_ * bias * velW_max_;
    vel_w_ = std::max(velW_max_,bias_w);
}
 