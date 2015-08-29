#include "Timer.hpp"

long CTimer::TimeSinceStart () {
	timespec Time;
	if (clock_gettime (CLOCK_REALTIME, &Time) == -1) {
		std::cout << "ERROR: SYSTEM CLOCK OFFLINE" << std::endl;
	}
	return (((Time.tv_sec - m_nTimerToZero) * 10000) + Time.tv_nsec / 100000);
}

int CTimer::InitTimer () {
	//Log_file->WriteTopic ("Init system timer", 1);
	timespec Time;
	if (clock_gettime (CLOCK_REALTIME, &Time) == -1) {
		//Log_file->Textout (RED, "Failed to initialise the timer!");
		return -1;
	}
	m_nTimerToZero = Time.tv_sec;
	//Log_file->Textout (BLACK, "Sytem timer initialised.");
	return 1;
}
