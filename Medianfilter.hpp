#ifndef MEDIANFILTER_HPP
#define MEDIANFILTER_HPP

#include <algorithm>
#include <vector>
#include <iostream>

class CMedianfilter
{
	public:
	CMedianfilter (int SizeOfFilter, int NumberOfDatapoints);
	void FilterData (int Data[]);
	int* GetFilteredData () {return m_nFilteredData;}
	
	private:
	int m_nSizeOfFilter;
	int m_nNumberOfDatapoints;
	int m_nData[]; 
	int m_nFilteredData[];
};

#endif