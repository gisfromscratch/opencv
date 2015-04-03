#pragma once

#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;

class ImageFile
{
public:
	ImageFile(const string &filePath);
	virtual ~ImageFile();

	string filePath();
	Mat* image();

private:
	string _filePath;
	Mat _image;
};

