#include <tao/img_features_matcher.hpp>
#include <math.h>

using namespace std;

namespace tao {

void FeaturesMatcher::match(tao::FeatureDescriptor& current, const tao::FeatureDescriptor& last)
{
	vector<bool> visited(false, last.size());
	int index_counter = last.size();
	
	for(int i = 0; i < current.size(); i++)
	{
		float dist_Min = 9999.9;
		int index_Min = 999;

		for(int j = 0; j < last.size(); j++)
		{
			if(visited[j] == false)
			{
				cv::Point2f central_point_current = current.central_points_[i];
				cv::Point2f central_point_last = last.central_points_[j];
				float perimeter_current = current.perimeters_[i];
				float perimeter_last = last.perimeters_[j];
				float dist = sqrt(pow(central_point_current.x - central_point_last.x, 2) + 
					pow(central_point_current.y - central_point_last.y, 2));
				dist += abs(perimeter_current - perimeter_last);

				if(dist < dist_Min)
				{
					dist_Min = dist;
					index_Min = j;
				}

			}
		}

		if(index_Min != 999)
		{
			visited[index_Min] = true;
			current.index_[i] = last.index_[index_Min];
		}
		else
		{
			current.index_[i] = (++index_counter);
		}
	}
}

}
