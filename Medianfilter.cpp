#include "Medianfilter.hpp"

CMedianfilter::CMedianfilter (int SizeOfFilter, int NumberOfDatapoints) {
	m_nSizeOfFilter = SizeOfFilter;
	m_nNumberOfDatapoints = NumberOfDatapoints;

	if (NumberOfDatapoints > 100) {
		std::cout << "DATASET FOR THE MEDIAN FILLTER IS TOO LARGE!" << std::endl;
	}
}

 void CMedianfilter::FilterData (int Data[]) {
	 std::vector<int> DataVec (m_nSizeOfFilter);

	for (int i=0;i<m_nNumberOfDatapoints; i++) {
		m_nFilteredData[i] = Data[i];
	}
	for (int i=(m_nSizeOfFilter/2); i<m_nNumberOfDatapoints-(m_nSizeOfFilter/2); i++) {
		for (int j=0; j<m_nSizeOfFilter; j++) {
			DataVec.push_back (Data[i+j]);
		}
		std::sort (DataVec.begin(), DataVec.end());
		m_nFilteredData[i] = DataVec[(m_nSizeOfFilter/2)+1];
		DataVec.clear ();
	}
	m_nFilteredData[m_nSizeOfFilter/2] = Data[m_nSizeOfFilter/2];
}