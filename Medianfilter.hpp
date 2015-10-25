#ifndef MEDIANFILTER_HPP
#define MEDIANFILTER_HPP

#include <algorithm>
#include <vector>
#include <iostream>
#include "Tracer.hpp"

class CMedianfilter
{
	public:
	CMedianfilter (int SizeOfFilter, int NumberOfDatapoints);
	void FilterData (int Data[]);
	int GetFilteredData (int i) {return m_nFilteredData[i];}

	private:
	int m_nSizeOfFilter;
	int m_nNumberOfDatapoints;
	std::vector<int> m_nFilteredData;
};

#endif