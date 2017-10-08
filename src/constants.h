#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef double Time;

namespace constants {
	const Time SIM_TIME(1000.0); // ms
	const Time H(0.5);
	const Time REFRACTORY_TIME(2.0); // ms
	const double SPIKE_THRESHOLD(20.0); // mV
	const double RESET_POTENTIAL(0.0); // mV Can use 10.0 as well (10.0 is given in the paper)
	const Time TAU(20.0); // ms
	const double C(1.0);
	const double MB_RESISTANCE(TAU/C);
}



#endif
