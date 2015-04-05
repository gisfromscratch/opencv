#include "ImageComparer.h"

#include <cmath>
#include <opencv2\imgproc\imgproc.hpp>


ImageComparer::ImageComparer(double threshold) : _threshold(threshold)
{
}


ImageComparer::~ImageComparer()
{
}


CompareResult ImageComparer::compare(Mat *image, Mat *otherImage)
{
	// Convert to Grayscale
	Mat imageAsGrayscale;
	Mat otherImageAsGrayscale;
	cvtColor(*image, imageAsGrayscale, COLOR_BGR2GRAY);
	cvtColor(*otherImage, otherImageAsGrayscale, COLOR_BGR2GRAY);

	// Detect the edges
	/*imageAsGrayscale = detectEdges(&imageAsGrayscale);
	otherImageAsGrayscale = detectEdges(&imageAsGrayscale);*/

	// Create the histograms
	MatND imageHistogram;
	MatND otherImageHistogram;
	const int NumberOfImages = 1;
	const int Dimension = 1;
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
	calcHist(&imageAsGrayscale, NumberOfImages, channels, mask, imageHistogram, Dimension, histogramSize, HistogramRanges, Uniform, Accumulate);
	calcHist(&otherImageAsGrayscale, NumberOfImages, channels, mask, otherImageHistogram, Dimension, histogramSize, HistogramRanges, Uniform, Accumulate);

	// Normalize the histograms
	const double Alpha = 0;
	const double Beta = 1;
	const int Type = -1;
	normalize(imageHistogram, imageHistogram, Alpha, Beta, NORM_MINMAX, Type, mask);
	normalize(otherImageHistogram, otherImageHistogram, Alpha, Beta, NORM_MINMAX, Type, mask);

	// Compare the normalized histograms
	const int CompareMethod = 0;
	double similarity = compareHist(imageHistogram, otherImageHistogram, CompareMethod);
	CompareResult compareResult(similarity, _threshold);
	return compareResult;
}


Mat ImageComparer::detectEdges(Mat *image)
{
	// Reduce noise with a kernel filter
	Mat detectedEdges;
	blur(*image, detectedEdges, Size(3, 3));

	// Detect the edges with Canny Edge Detector
	const int EdgeThresh = 1;
	const int LowThreshold = 0;
	const int MaxLowThreshold = 100;
	const int Ratio = 3;
	const int KernelSize = 3;
	Canny(detectedEdges, detectedEdges, LowThreshold, LowThreshold * Ratio, KernelSize);
	return detectedEdges;
}