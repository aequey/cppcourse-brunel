#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <cassert>

typedef double Milliseconds;
typedef double Time;

namespace constants {
	constexpr Milliseconds SIM_TIME(500.0); // ms
	constexpr Milliseconds SIM_STEP(0.1); // ms
	const Time H(1);
	constexpr Milliseconds REFRACTORY_TIME(2.0); // ms
	const double SPIKE_THRESHOLD(20.0); // mV
	const double RESET_POTENTIAL(0.0); // mV Can use 10.0 as well (10.0 is given in the paper)
	const double J(0.2); // mV Amplitude of the spike
	constexpr Milliseconds TAU(20.0); // ms
	constexpr double C(1.0); // mA
}



#endif
