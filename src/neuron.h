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
	bool update(const Time& stopTime);
	bool update(const double& extI, const Time& stopTime, const double& noise);
	void receiveSpike(const Potential& amplitude, const Time & delay);
	
	Potential getMbPotential() const;
	unsigned int getNbSpikes() const;
	Time getSpikeTime() const;
private :
	Potential mbPotential;
	unsigned int nbSpikes;
	Time lastSpike;
	Time currentTime;
	std::array<Potential, constants::D_IN_STEP+1> buffer;
	
	static constexpr Time refractoryStep = (constants::REFRACTORY_TIME/constants::H);
	static constexpr double mbResistance = (constants::TAU/constants::C);
	static constexpr double ODEFactor1 = (exp(-constants::H/constants::TAU));
	static constexpr double ODEFactor2 = (mbResistance*(1-ODEFactor1));

	bool isRefractory();
	void updatePotential(const double& extI, const Potential& J, const double& noise);
	unsigned int inBuffer(const Time&) const;
};

#endif // NEURON_H
