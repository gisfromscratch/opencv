#include "ImageComparer.h"

#include <cmath>
#include <opencv2\imgproc\imgproc.hpp>


ImageComparer::ImageComparer(double thresold) : _thresold(thresold)
{
}


ImageComparer::~ImageComparer()
{
}


int ImageComparer::compare(Mat *image, Mat *otherImage)
{
	// Convert to HSV
	Mat imageAsHsv;
	Mat otherImageAsHsv;
	cvtColor(*image, imageAsHsv, COLOR_BGR2HSV);
	cvtColor(*otherImage, otherImageAsHsv, COLOR_BGR2HSV);

	// Create the histograms
	MatND imageHistogram;
	MatND otherImageHistogram;
	const int NumberOfImages = 1;
	const int Dimension = 2;
	const int Hue = 50;
	const int Saturation = 60;
	int histogramSize[] = { Hue, Saturation };
	float hueRange[] = { 0, 180 };
	float saturationRange[] = { 0, 256 };
	const float *HistogramRanges[] = { hueRange, saturationRange };
	int channels[] = { 0, 1 };
	const bool Uniform = true;
	const bool Accumulate = false;
	Mat mask = Mat();
	calcHist(&imageAsHsv, NumberOfImages, channels, mask, imageHistogram, Dimension, histogramSize, HistogramRanges, Uniform, Accumulate);
	calcHist(&otherImageAsHsv, NumberOfImages, channels, mask, otherImageHistogram, Dimension, histogramSize, HistogramRanges, Uniform, Accumulate);

	// Normalize the histograms
	const double Alpha = 0;
	const double Beta = 1;
	const int Type = -1;
	normalize(imageHistogram, imageHistogram, Alpha, Beta, NORM_MINMAX, Type, mask);
	normalize(otherImageHistogram, otherImageHistogram, Alpha, Beta, NORM_MINMAX, Type, mask);

	// Compare the normalized histograms
	const int CompareMethod = 0;
	double compareResult = compareHist(imageHistogram, otherImageHistogram, CompareMethod);
	if (_thresold <= fabs(compareResult))
	{
		return 0;
	}
	else
	{
		if (compareResult < 0)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
}
