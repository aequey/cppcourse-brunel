#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <cassert>

typedef double Milliseconds;
typedef unsigned int Time;
typedef double Potential;

namespace constants {
	constexpr Milliseconds SIM_TIME(500.0); // [ms]
	constexpr Milliseconds H(0.1); // [ms]
	constexpr Milliseconds REFRACTORY_TIME(2.0); // [ms]
	const Potential SPIKE_THRESHOLD(20.0); // [mV]
	const Potential RESET_POTENTIAL(0.0); // [mV] Can use 10.0 as well (10.0 is given in the paper)
	const Potential JE(0.1); // [mV] Amplitude of the spike
	const double G(3.0);
	const double ETA(0.2);
	const Potential JI(JE*G);
	const Milliseconds D(1.5); // [ms] Delay of the spike
	const Time D_IN_STEP(D/H);
	constexpr Milliseconds TAU(20.0); // [ms]
	constexpr double C(1.0); // [mA]
	const unsigned int N_TOTAL(12500);
	//~ const double E_RATE(0.8);
	const unsigned int NE(10000);
	const unsigned int NI(2500);
	const double CONNEXION_RATE(0.1);
	const unsigned int CE(NE*CONNEXION_RATE);
	const unsigned int CI(NI*CONNEXION_RATE);

	
}



#endif
