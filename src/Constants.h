#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <cassert>


typedef double Milliseconds;
typedef unsigned int Time;
typedef double Potential;


namespace constants {
	
	// parameters to change to reproduse Fig. 8 of the paper
		// G = |JI|/|JE| the rate between amplitude of the spike sent by inhibitory and excitatory Neuron
		// Brunel simulations : A) 3.0 ; B) 6.0 ; C) 5.0 ; D) 4.5
		const double G(5.0);
		// ETA = NU_EXT/NU_THR a parameter given in Brunel's paper that indicates the quantity of neurons that are spiking from the outside
		// Brunel simulations : A) 2.0 : B) 4.0 ; C) 2.0 ; D) 0.9
		const double ETA(2.0);

	// general Simulation parameters
		// The default Simulation time (in Milliseconds)
		constexpr Milliseconds SIM_TIME(1000.0);
		// The time corresponding to a simulation step (in Milliseconds)
		constexpr Milliseconds H(0.1);
	
	// Neuron parameters
		// The membrane potential threshold for a spike (in Millivolts)
		const Potential SPIKE_THRESHOLD(20.0);
		// The membrane potential a Neuron has at the beginning of the Simulation or after a spike (in Millivolts)
		const Potential RESET_POTENTIAL(10.0); // (10.0 is given in the paper, 0.0 in the lecture. We use the paper values for accurate results)
		// The time a Neuron is refractory after the sending of a spike (in Milliseconds)
		constexpr Milliseconds REFRACTORY_TIME(2.0);
		// TAU = R*C (in Milliseconds)
		constexpr Milliseconds TAU(20.0);
		// C is given in Milliampers
		constexpr double C(1.0);
	
	// Spiking parameters
		// Amplitude of a spike sent by an excitatory Neuron (in Millivolts)
		const Potential JE(0.1);
		// Amplitude of a spike sent by an inhibitory Neuron (in Millivolts)
		const Potential JI(-JE*G);
		// Delay of the tramsmission of a spike (in Milliseconds)
		const Milliseconds D(1.5);
		// Delay of the tramsmission of a spike (in Time steps)
		const Time D_IN_STEP(D/H);
	
	// Network parameters
		// Total number of neurons
		const unsigned int N_TOTAL(12500);
		// Number of excitatory neurons
		const unsigned int NE(10000);
		// Number of inhibitory neurons
		const unsigned int NI(2500);
		
		// The proportion of neurons each Neuron is connected with (input)
		const double CONNEXION_RATE(0.1);
		// The number of excitatory neurons in input for each Neuron
		const unsigned int CE(NE*CONNEXION_RATE);
		// The number of inhibitory neurons in input for each Neuron
		const unsigned int CI(NI*CONNEXION_RATE);
		
		// The value of lambda of the Poisson distribution used to determine the number of external neurons that spike.
		const double DISTRIBUTION(ETA*SPIKE_THRESHOLD*H/(TAU*JE));
}



#endif
