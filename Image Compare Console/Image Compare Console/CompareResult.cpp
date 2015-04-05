#include "CompareResult.h"

#include <cmath>
#include <limits>

using namespace std;


CompareResult::CompareResult(double similarity, double threshold) : _similarity(similarity), _threshold(threshold)
{
}


CompareResult::~CompareResult()
{
}


bool CompareResult::isIdentical()
{
	return _threshold < (fabs(_similarity) + numeric_limits<double>::epsilon());
}


double CompareResult::similarity()
{
	return _similarity;
}


double CompareResult::threshold()
{
	return _threshold;
}