#ifndef NEURON_H
#define NEURON_H

#include "constants.h"
#include "simulation.h"
#include <array>

class Simulation;

class Neuron {
public :
	Neuron();
	~Neuron() = default;
	
	bool update(const double& extI, const Time& stopTime);
	void receiveSpike(const double& amplitude, const Time & delay);
	
	double getMbPotential() const;
	unsigned int getNbSpikes() const;
	Time getSpikeTime() const;
private :
	double mbPotential;
	unsigned int nbSpikes;
	Time lastSpike;
	Time currentTime;
	std::array<double, constants::D_IN_STEP+1> buffer;
	//~ unsigned int timeInBuffer;
	
	static constexpr Time refractoryStep = (constants::REFRACTORY_TIME/constants::H);
	static constexpr double mbResistance = (constants::TAU/constants::C);
	static constexpr double ODEFactor1 = (exp(-constants::H/constants::TAU));
	static constexpr double ODEFactor2 = (mbResistance*(1-ODEFactor1));

	bool isRefractory();
	void updatePotential(const double& extI, const double& J);
	unsigned int inBuffer(const Time&) const;
};

#endif // NEURON_H
