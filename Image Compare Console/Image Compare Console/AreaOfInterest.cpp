#include "AreaOfInterest.h"


AreaOfInterest::AreaOfInterest()
{
}


AreaOfInterest::~AreaOfInterest()
{
}


void AreaOfInterest::add(int xFrom, int xTo, int yFrom, int yTo)
{
	for (int rowIndex = xFrom; rowIndex <= xTo; rowIndex++)
	{
		std::map<int, std::set<int> >::iterator regionIterator = _regions.find(rowIndex);
		if (_regions.end() == regionIterator)
		{
			// Insert new row region
			std::set<int> columns;
			for (int columnIndex = yFrom; columnIndex <= yTo; columnIndex++)
			{
				columns.insert(columnIndex);
			}
			_regions[rowIndex] = columns;
		}
		else
		{
			// Add to existing row region
			std::set<int> existingColumns = regionIterator->second;
			for (int columnIndex = yFrom; columnIndex <= yTo; columnIndex++)
			{
				if (existingColumns.end() == existingColumns.find(columnIndex))
				{
					// Insert new column
					existingColumns.insert(columnIndex);
				}
			}
		}
	}
}


bool AreaOfInterest::contains(int x, int y)
{
	std::map<int, std::set<int> >::iterator regionIterator = _regions.find(x);
	if (_regions.end() == regionIterator)
	{
		return false;
	}

	std::set<int> existingColumns = regionIterator->second;
	std::set<int>::iterator columnIterator = existingColumns.find(y);
	if (existingColumns.end() == columnIterator)
	{
		return false;
	}

	return true;
}


bool AreaOfInterest::containsAny(int xFrom, int xTo, int yFrom, int yTo)
{
	for (int rowIndex = xFrom; rowIndex <= xTo; rowIndex++)
	{
		for (int columnIndex = yFrom; columnIndex <= yTo; columnIndex++)
		{
			if (contains(rowIndex, columnIndex))
			{
				return true;
			}
		}
	}

	return false;
}