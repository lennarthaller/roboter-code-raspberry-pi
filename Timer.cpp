#include "Timer.hpp"

long CTimer::TimeSinceStart () {
	timespec Time;
	if (clock_gettime (CLOCK_REALTIME, &Time) == -1) {
		std::cout << "ERROR: SYSTEM CLOCK OFFLINE" << std::endl;
	}
	return (((Time.tv_sec - m_nTimerToZero) * 10000) + Time.tv_nsec / 100000);
}

int CTimer::InitTimer () {
	timespec Time;
	if (clock_gettime (CLOCK_REALTIME, &Time) == -1) {
		g_pTracer->Trace (ERROR, "Failed to initialise the timer!");
		return -1;
	}
	m_nTimerToZero = Time.tv_sec;
	g_pTracer->Trace (NOTE, "Sytem timer initialised.");
	return 1;
}
