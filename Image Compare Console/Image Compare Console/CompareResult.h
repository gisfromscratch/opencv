#pragma once
class CompareResult
{
public:
	CompareResult(double similarity = 0.0, double thresold = 0.75);
	virtual ~CompareResult();

	bool isIdentical();
	double similarity();
	double thresold();

private:
	double _similarity;
	double _thresold;
};

