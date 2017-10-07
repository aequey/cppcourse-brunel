#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef double Time;

namespace constants {
	const Time SIM_TIME(2000.0); // ms
	const Time H(1.0);
	const Time REFRACTORY_TIME(2.0); // ms
	const double SPIKE_THRESHOLD(20.0); // mV
	const double RESET_POTENTIAL(10.0); // mV
	const Time TAU(20.0); // ms
	const double C(1.0);
	const double MB_RESISTANCE(TAU/C);
}



#endif
