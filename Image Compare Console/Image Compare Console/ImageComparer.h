#pragma once

#include <opencv2\core\core.hpp>

#include "CompareResult.h"

using namespace cv;

class ImageComparer
{
public:
	ImageComparer(double threshold = 0.75);
	virtual ~ImageComparer();

	CompareResult compare(Mat *image, Mat *otherImage);

private:
	Mat detectEdges(Mat *image);

	double _threshold;
};

