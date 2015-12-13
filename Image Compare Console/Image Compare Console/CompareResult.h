#pragma once
class CompareResult
{
public:
	CompareResult(double similarity = 0.0, double threshold = 0.75);
	virtual ~CompareResult();

	bool isIdentical();
	double similarity();
	double threshold();

private:
	double _similarity;
	double _threshold;
};

