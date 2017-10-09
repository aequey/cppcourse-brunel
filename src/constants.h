#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>

typedef double Time;

namespace constants {
	const Time SIM_TIME(500.0); // ms
	const Time H(0.5); // ms
	const int SIM_STEP(SIM_TIME/H);
	const Time REFRACTORY_TIME(2.0); // ms
	const double SPIKE_THRESHOLD(20.0); // mV
	const double RESET_POTENTIAL(0.0); // mV Can use 10.0 as well (10.0 is given in the paper)
	const Time TAU(20.0); // ms
	const double C(1.0);
	const double MB_RESISTANCE(TAU/C);
	const double FACTOR1 (exp(-H/TAU));
	const double FACTOR2 (MB_RESISTANCE*(1-FACTOR1));

}



#endif
