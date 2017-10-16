#ifndef NEURON_H
#define NEURON_H

#include "constants.h"
#include "simulation.h"
#include <vector>

class Simulation;

class Neuron {
public :
	Neuron();
	~Neuron() = default;
	
	bool update(const double& extI, const Time& stopTime);
	void receiveSpike(const double& amplitude);
	
	double getMbPotential() const;
	unsigned int getNbSpikes() const;
	Time getSpikeTime() const;
private :
	double mbPotential;
	double J;
	unsigned int nbSpikes;
	Time lastSpike;
	Time currentTime;
	
	
	static constexpr Time refractoryStep = (constants::REFRACTORY_TIME/constants::H);
	static constexpr double mbResistance = (constants::TAU/constants::C);
	static constexpr double ODEFactor1 = (exp(-constants::H/constants::TAU));
	static constexpr double ODEFactor2 = (mbResistance*(1-ODEFactor1));

	bool isRefractory();
	void updatePotential(const double& extI);
};

#endif // NEURON_H
