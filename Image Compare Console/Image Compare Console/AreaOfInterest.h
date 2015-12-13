#pragma once

#include <map>
#include <set>

class AreaOfInterest
{
public:
	AreaOfInterest();
	~AreaOfInterest();

	void add(int xFrom, int xTo, int yFrom, int yTo);

	bool contains(int x, int y);
	bool containsAny(int xFrom, int xTo, int yFrom, int yTo);

private:
	std::map<int, std::set<int> > _regions;
};

