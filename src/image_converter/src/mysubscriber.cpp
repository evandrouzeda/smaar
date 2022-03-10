#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

namespace enc = sensor_msgs::image_encodings;

bool hasWhite(cv::Mat mask){
    for (size_t x = 0; x < mask.rows; x++)
    {
        for (size_t y = 0; y < mask.cols; y++)
        {
            if(mask.at<uchar>(x, y) == 255)
                return true;
        }
    }
    return false;
}

void imageCallback(const sensor_msgs::ImageConstPtr& msg){
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
        cv::waitKey(30);
    }
    catch(cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
    cv::Mat up_red_mask, lo_red_mask, red_mask, lo_green_mask, up_green_mask, green_mask,img_hsv; 
	cv::cvtColor(cv_ptr->image,img_hsv,cv::COLOR_BGR2HSV);

    cv::imshow("teste1", cv_ptr->image);
    cv::waitKey(30);

    cv::imshow("teste2", img_hsv);
    cv::waitKey(30);

	cv::inRange(img_hsv,cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255),lo_red_mask); 
	cv::inRange(img_hsv,cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255),up_red_mask); 
    cv::addWeighted(lo_red_mask, 1.0, up_red_mask, 1.0, 0.0, red_mask);
    cv::imshow("red", red_mask);
    cv::waitKey(30);

    cv::inRange(img_hsv,cv::Scalar(30, 100, 100), cv::Scalar(80, 255, 255),green_mask);
    cv::imshow("green", green_mask);
    cv::waitKey(30);
    
    
    if(hasWhite(red_mask))
        std::cout << "é inimigo";
    else if(hasWhite(green_mask))
        std::cout << "é amigo";
    else std::cout << "é civil";

    /* cv::destroyWindow("red");
    cv::destroyWindow("green"); */
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_listener");
    ros::NodeHandle nh;

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("camera/image", 1, imageCallback);
    ros::spin();
    
    return 0;
}