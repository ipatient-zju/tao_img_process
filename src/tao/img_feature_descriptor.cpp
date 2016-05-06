#include <tao/img_feature_descriptor.hpp>

using namespace std;

namespace tao {

FeatureDescriptor::FeatureDescriptor(const vector< vector<cv::Point2f> > contours)
{
	for(int i = 0; i < contours.size(); i++)
	{
		vector<cv::Point2f> contour = contours[i];
		//将每一个contours传给contour
		cv::Point2f central_point(0.0, 0.0);
		//中心点初始化为（0.0,0.0）
		float perimeter = (float)contour.size();
		//
		int index = (i+1);
		//目录加一

		for(int j = 0; j < contour.size(); j++)
		{
			central_point.x += contour[j].x;
			central_point.y += contour[j].y;
		}

		central_point.x /= perimeter;
		central_point.y /= perimeter;

		central_points_.push_back(central_point);
		perimeters_.push_back(perimeter);
		index_.push_back(index);
	}
}

}
