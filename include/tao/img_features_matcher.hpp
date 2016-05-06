#ifndef __TAO_IMG_FEATURES_MATCHER_HPP__
#define __TAO_IMG_FEATURES_MATCHER_HPP__

#include <tao/img_feature_descriptor.hpp>
#include <opencv2/opencv.hpp>

using namespace std;

namespace tao {

class FeaturesMatcher{

public:
	FeaturesMatcher() {}
	~FeaturesMatcher() {}
	void match(tao::FeatureDescriptor& current, const tao::FeatureDescriptor& last);
};

}

#endif /* __TAO_IMG_FEATURE_MATCHER_HPP__ */
