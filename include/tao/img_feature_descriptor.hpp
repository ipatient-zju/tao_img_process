#ifndef __TAO_IMG_FEATURE_DESCRIPTOR_HPP__
#define __TAO_IMG_FEATURE_DESCRIPTOR_HPP__

#include <opencv2/opencv.hpp>

using namespace std;

namespace tao {
//声明类FeatureDescripto
//类的一个特征就是封装，public和private作用就是实现这一目的。所以：
//用户代码（类外）可以访问public成员而不能访问private成员；private成员只能由类成员（类内）和友元访问。
//类的另一个特征就是继承，protected的作用就是实现这一目的。所以：
//protected成员可以被派生类对象访问，不能被用户代码（类外）访问。
class FeatureDescriptor{

public:
	FeatureDescriptor() {}
	FeatureDescriptor(const vector< vector<cv::Point2f> > contours);
	//析构函数，清零
	~FeatureDescriptor()
	{
		if(index_.size() != 0)
			index_.clear();
		
		if(central_points_.size() != 0)
			central_points_.clear();

		if(perimeters_.size() != 0)
		//周长，边缘
			perimeters_.clear();
	}
	//
	void calculateFeature(const vector< vector<cv::Point2f> > contours)
	{
		(*this) = tao::FeatureDescriptor(contours);
	}

	int size() const
	{
		return index_.size();
	}

public:
	vector<cv::Point2f> central_points_;
	vector<float> perimeters_;
	vector<int> index_;
};

}

#endif /* __TAO_IMG_FEATURE_DESCRIPTOR_HPP__ */
