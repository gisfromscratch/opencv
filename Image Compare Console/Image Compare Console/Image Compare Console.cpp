// Image Compare Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

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

//int _tmain(int argc, _TCHAR* argv[])

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int commandShow)
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

	return 0;
}
