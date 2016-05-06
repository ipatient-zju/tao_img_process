#include <tao/img_frontend.hpp>

namespace tao {

bool ImgFrontend::run()
{
	cv::FileStorage fs(calibFileName, cv::FileStorage::READ);
	if (!fs.isOpened())
	{
		std::cout << "Could not open the calibration file: \"" << calibFileName << "\"" << std::endl;
		return false;
	}

	fs["Camera_Matrix"] >> cameraMatrix;
	fs["Distortion_Coefficients"] >> distCoeffs;

	fs.release();
	undistImg = true;
	std::cout << "Calibration file read done!" << std::endl;

	image_sub_ = it_.subscribe(iImgTopic, 1, &ImgFrontend::imgCallBack, this);
	image_pub_ = it_.advertise(oImgTopic, 1);

	if (showImg)
	{
		cv::namedWindow("Original");
		cv::namedWindow("Undistorted");
	}

	return true;
}

void ImgFrontend::imgCallBack(const sensor_msgs::ImageConstPtr& msg)
{
	cv_bridge::CvImagePtr cv_ptr;
	try
	{
		cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}
	
	cv::Mat temp = cv_ptr->image.clone();
	cv::undistort(temp, cv_ptr->image, cameraMatrix, distCoeffs);
	//Transforms an image to compensate for lens distortion
	//void undistort( InputArray src, OutputArray dst, InputArray cameraMatrix, InputArray distCoeffs,InputArray newCameraMatrix=noArray() )
	//此时输出image已校正过

	if (showImg)
	{
		cv::imshow("Original", temp);
		cv::imshow("Undistorted", cv_ptr->image);
		cv::waitKey(3);
	}
	//将cv image 转化为ros　类型，并发布
	image_pub_.publish(cv_ptr->toImageMsg());
}

}
