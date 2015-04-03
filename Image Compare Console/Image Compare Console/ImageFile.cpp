#include "ImageFile.h"

#include <opencv2\highgui\highgui.hpp>

ImageFile::ImageFile(const string &filePath) : _filePath(filePath)
{
}


ImageFile::~ImageFile()
{
}


string ImageFile::filePath()
{
	return _filePath;
}


Mat* ImageFile::image()
{
	_image = imread(_filePath, IMREAD_COLOR);
	return &_image;
}
