/** 
 * This file is part of tao.
 *
 */

#ifndef __IMG_LOCALIZATION_HPP__
#define __IMG_LOCALIZATION_HPP__

#include <ros/ros.h>
// #include <ros/console.h>

#include <geometry_msgs/Point.h>
#include <px_comm/OpticalFlow.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>

#include <message_filters/subscriber.h>
// publisher tf
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <opencv2/opencv.hpp>

#include <iostream>
#include <sstream>

//主要解决image,imu,px4flow帧率不同的同步问题；
namespace tao
{

//A message filter is defined as something which a message arrives into and may or may not be spit back out of at a later point in time.

//An example is the time synchronizer, which takes in messages of different types from multiple sources, and outputs them only if it has received a message on each of those sources with the same timestamp. 

//The TimeSynchronizer filter synchronizes incoming channels by the timestamps contained in their headers, and outputs them in the form of a single callback that takes the same number of channels
typedef message_filters::sync_policies::ApproximateTime<geometry_msgs::Point, px_comm::OpticalFlow> EulerWithOptFlowPolicy;
typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::CameraInfo> ImageWithCameraInfoPolicy;

class ImgLocalization
{
protected:
	ros::NodeHandle nh_;
	ros::NodeHandle nh_param_;

	message_filters::Subscriber<geometry_msgs::Point> imu_subscriber_;
	message_filters::Subscriber<px_comm::OpticalFlow> px4flow_subscriber_;
	message_filters::Subscriber<sensor_msgs::Image> image_subscriber_;
	message_filters::Subscriber<sensor_msgs::CameraInfo> camera_info_subscriber_;

	message_filters::Synchronizer<EulerWithOptFlowPolicy> imu_px4_synchronizer_;
	message_filters::Synchronizer<ImageWithCameraInfoPolicy> image_camera_info_synchronizer_;

	bool isSynchronizedMsgsStreamRunning();

	void startSynchronizedMsgsStream();
	void stopSynchronizedMsgsStream();

public:
	ImgLocalization(ros::NodeHandle& nh, ros::NodeHandle& nh_param);
	~ImgLocalization();

	void handleEulerAndOptFlow(const geometry_msgs::PointConstPtr& imu_msg,
			const px_comm::OpticalFlow& px4_msg);
	void handleImage(const sensor_msgs::ImagaConstPtr& image_msg,
			const sensor_msgs::CameraInfoConstPtr& camera_info_msg);

private:
	message_filters::Connection connection;
	bool connected;

};

}

#endif /* __IMG_LOCALIZATION_HPP__ */
