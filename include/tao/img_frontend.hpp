/*! \file img_frontend.hpp
 *  \brief 
 */

#ifndef __TAO_IMG_FRONTEND_HPP__
#define __TAO_IMG_FRONTEND_HPP__

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

#include <iostream>
#include <sstream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace tao {

class ImgFrontend{

public:
	ImgFrontend(ros::NodeHandle& nh, ros::NodeHandle& nh_private) : it_(nh), nh_private_(nh_private)
	{}

	~ImgFrontend()
	{
		if (showImg)
		{
			cv::destroyWindow("Original");
			cv::destroyWindow("Undistorted");
		}

		if (undistImg)
		{
			cameraMatrix.release();
			distCoeffs.release();
		}
	}

	void configure()
	{
		nh_private_.param("showImg", showImg, false);
		nh_private_.param("undistImg", undistImg, true);
		nh_private_.param("calibFileName", calibFileName, std::string("default.xml"));
		nh_private_.param("iImgTopic", iImgTopic, std::string("/camera/image_color"));
		nh_private_.param("oImgTopic", oImgTopic, std::string("/img_frontend/image_undist"));
	}

	bool run();

private:
	void imgCallBack(const sensor_msgs::ImageConstPtr& msg);

public:
	cv::Mat cameraMatrix;
	cv::Mat distCoeffs;

private:
	bool showImg;
	bool undistImg;
	std::string calibFileName;
	std::string iImgTopic;
	std::string oImgTopic;
	ros::NodeHandle nh_private_;
	//ros::NodeHandle nh;
	//ros::Publisher endpoint_pub;
	image_transport::ImageTransport it_;
	image_transport::Subscriber image_sub_;
	image_transport::Publisher image_pub_;
	

};

}

#endif /* __TAO_IMG_FRONTEND_HPP__ */
