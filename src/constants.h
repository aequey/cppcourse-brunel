#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <cassert>

typedef double Milliseconds;
typedef double Time;

namespace constants {
	const Milliseconds SIM_TIME(500.0); // ms
	const Milliseconds SIM_STEP(0.1); // ms
	const Time TOTAL_STEP(SIM_TIME/SIM_STEP);
	const Time H(1);
	const Milliseconds REFRACTORY_TIME(2.0); // ms
	const Time REFRACTORY_STEP(REFRACTORY_TIME/SIM_STEP);
	const double SPIKE_THRESHOLD(20.0); // mV
	const double RESET_POTENTIAL(0.0); // mV Can use 10.0 as well (10.0 is given in the paper)
	const Milliseconds TAU(20.0); // ms
	const double C(1.0); // mA ?
	const double MB_RESISTANCE(TAU/C);
	const double FACTOR1 (exp(-SIM_STEP/TAU));
	const double FACTOR2 (MB_RESISTANCE*(1-FACTOR1));

}



#endif
