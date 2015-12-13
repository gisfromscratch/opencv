// Image Compare Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include "AreaOfInterest.h"
#include "CompareResult.h"
#include "ImageComparer.h"
#include "ImageFile.h"

using namespace cv;
using namespace std;

static ImageFile readImage(const string &imagePath)
{
	ImageFile imageFile(imagePath);
	return imageFile;
}

static bool addImage(vector<ImageFile> &images, const string &imagePath)
{
	ImageFile imageFile = readImage(imagePath);
	if (imageFile.image()->data)
	{
		images.push_back(imageFile);
		return true;
	}
	return false;
}

static void ImageCompareExample()
{
	ImageFile imageFile = readImage("C:\\DoubleRightFilledImage.jpg");
	if (imageFile.image()->data)
	{
		// Read known images
		vector<ImageFile> imageFiles;
		addImage(imageFiles, "C:\\2005-06_Kolodziejski_Artur[1].jpg");
		addImage(imageFiles, "C:\\2005-06_Kolodziejski_Artur[2].jpg");
		addImage(imageFiles, "C:\\2005-06_Kolodziejski_Artur[3].jpg");
		addImage(imageFiles, "C:\\DoubleImage.jpg");
		addImage(imageFiles, "C:\\DoubleLeftImage.jpg");
		addImage(imageFiles, "C:\\DoubleRightImage.jpg");
		addImage(imageFiles, "C:\\1995-96_Kramer_Arvid[1].jpg");

		ImageComparer imageComparer(0.75);
		for (vector<ImageFile>::iterator iterator = imageFiles.begin(); iterator != imageFiles.end(); iterator++)
		{
			ImageFile knownImageFile = *iterator;
			Mat *knownImage = knownImageFile.image();
			CompareResult compareResult = imageComparer.compare(imageFile.image(), knownImage);
			if (compareResult.isIdentical())
			{
				string windowCaption = to_string(compareResult.similarity()) + " " + knownImageFile.filePath();
				namedWindow(windowCaption, WINDOW_AUTOSIZE);
				imshow(windowCaption, *knownImage);
			}
		}

		waitKey(0);
	}
}


static void findMatches(int, void*)
{

}


static void TemplateMatchExample(string &sourceFilePath, string &templateFilePath)
{
	ImageFile sourceImageFile = readImage(sourceFilePath);
	ImageFile templateImageFile = readImage(templateFilePath);
	Mat *sourceImage = sourceImageFile.image(); 
	Mat *templateImage = templateImageFile.image();
	if (sourceImage->data && templateImage->data)
	{
		// Copy the image to display
		Mat displayImage;
		sourceImage->copyTo(displayImage);

		// Show the original image
		string windowCaption = sourceImageFile.filePath();
		namedWindow(windowCaption, WINDOW_AUTOSIZE);
		imshow(windowCaption, displayImage);
		waitKey(0);

		// Create the result
		int columnCount = sourceImage->cols - templateImage->cols + 1;
		int rowCount = sourceImage->rows - templateImage->rows + 1;
		assert(0 < columnCount && 0 < rowCount);
		Mat resultImage;
		resultImage.create(rowCount, columnCount, CV_32FC1);

		// Matching and Normalizing
		matchTemplate(*sourceImage, *templateImage, resultImage, CV_TM_SQDIFF);
		normalize(resultImage, resultImage, 0, 1, NORM_MINMAX, -1, Mat());

		// Localizing the best match
		double minVal;
		double maxVal; 
		Point minLoc; 
		Point maxLoc;
		minMaxLoc(resultImage, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		Point matchLoc = minLoc;

		// Find all matches using a thresold
		AreaOfInterest aoi;
		double thresholdValue = 0.01;
		Mat thresholdImage;
		thresholdImage.create(rowCount, columnCount, CV_32FC1);
		threshold(resultImage, thresholdImage, thresholdValue, 255, CV_THRESH_BINARY);
		for (int rowIndex = 0; rowIndex < rowCount; rowIndex++)
		{
			for (int columnIndex = 0; columnIndex < columnCount; columnIndex++)
			{
				if (0 == thresholdImage.at<unsigned int>(rowIndex, columnIndex))
				{
					if (!aoi.containsAny(rowIndex, rowIndex + templateImage->rows, columnIndex, columnIndex + templateImage->cols))
					{
						// Add the rectangle
						Point upperLeft(columnIndex, rowIndex);
						Point lowerRight(columnIndex + templateImage->cols, rowIndex + templateImage->rows);
						rectangle(displayImage, upperLeft, lowerRight, Scalar::all(253), 2, 8, 0);

						aoi.add(rowIndex, rowIndex + templateImage->rows, columnIndex, columnIndex + templateImage->cols);

						// Adjust the indices
						columnIndex = lowerRight.x;
					}
				}
			}
		}

		// Show the result
		//rectangle(displayImage, matchLoc, Point(matchLoc.x + templateImage->cols, matchLoc.y + templateImage->rows), Scalar::all(253), 2, 8, 0);
		//rectangle(resultImage, matchLoc, Point(matchLoc.x + templateImage->cols, matchLoc.y + templateImage->rows), Scalar::all(0), 2, 8, 0);

		namedWindow(windowCaption, WINDOW_AUTOSIZE);
		imshow(windowCaption, displayImage);

		waitKey(0);
	}
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int commandShow)
{
	string commandLineArgs(commandLine);
	regex commandLineRegex("\\s+");
	sregex_token_iterator commandLineArgIterator(commandLineArgs.begin(), commandLineArgs.end(), commandLineRegex, -1);
	sregex_token_iterator iteratorEnd;
	vector<string> arguments;
	while (iteratorEnd != commandLineArgIterator) {
		arguments.push_back(commandLineArgIterator->str());
		commandLineArgIterator++;
	}
	if (2 == arguments.size())
	{
		try {
			TemplateMatchExample(arguments[0], arguments[1]);
		}
		catch (cv::Exception ex) {
			cerr << ex.msg << endl; 
		}
	}

	return 0;
}
