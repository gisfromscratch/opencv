#pragma once

#include <opencv2\core\core.hpp>

using namespace cv;

class ImageComparer
{
public:
	ImageComparer(double thresold = 0.75);
	virtual ~ImageComparer();

	int compare(Mat *image, Mat *otherImage);

private:
	double _thresold;
};

