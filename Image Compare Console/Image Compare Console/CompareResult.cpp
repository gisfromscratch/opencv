#include "CompareResult.h"

#include <cmath>
#include <limits>

using namespace std;


CompareResult::CompareResult(double similarity, double thresold) : _similarity(similarity), _thresold(thresold)
{
}


CompareResult::~CompareResult()
{
}


bool CompareResult::isIdentical()
{
	return _thresold < (fabs(_similarity) + numeric_limits<double>::epsilon());
}


double CompareResult::similarity()
{
	return _similarity;
}


double CompareResult::thresold()
{
	return _thresold;
}