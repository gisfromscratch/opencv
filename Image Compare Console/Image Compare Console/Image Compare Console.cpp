// Image Compare Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	Mat image = imread("D:\\2005-06_Kolodziejski_Artur[1].jpg", IMREAD_COLOR);
	if (image.data)
	{
		namedWindow("Image Viewer", WINDOW_AUTOSIZE);
		imshow("Image Viewer", image);
		waitKey(0);
	}

	return 0;
}

