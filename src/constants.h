#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef double Time;

namespace constants {
	const Time SIM_TIME(1000.0); // ms
	const Time H(1.0);
	const Time REFRACTORY_TIME(2.0); // ms
	const double SPIKE_THRESHOLD(20.0); // mV
	const double MB_RESISTANCE(10.0);
	const double RESET_POTENTIAL(10.0); // mV
	const Time TAU(20.0);
}



#endif
