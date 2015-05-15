#include "Medianfilter.hpp"

CMedianfilter::CMedianfilter (int SizeOfFilter, int NumberOfDatapoints) {
	m_nSizeOfFilter = SizeOfFilter;
	m_nNumberOfDatapoints = NumberOfDatapoints;
}

 void CMedianfilter::FilterData (int Data[]) {
	 std::vector<int> DataVec (m_nSizeOfFilter);
	 
	for (int i=0;i<m_nNumberOfDatapoints; i++) {
		m_nData[i] = Data[i];
		m_nFilteredData[i] = Data[i];
	}
	for (int i=(m_nSizeOfFilter/2); i<m_nNumberOfDatapoints-(m_nSizeOfFilter/2); i++) {
		for (int j=0; j<m_nSizeOfFilter; j++) {
			DataVec.push_back (m_nData[i+j]);
		}
		std::sort (DataVec.begin(), DataVec.end());
		m_nFilteredData[i] = DataVec[(m_nSizeOfFilter/2)+1];
		DataVec.clear ();
	}
}