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
	
	void update(const double& extI, const Time& stopTime);
	double getMbPotential() const;
	unsigned int getNbSpikes() const;
	Time getSpikeTime() const;
private :
	double mbPotential;
	unsigned int nbSpikes;
	Time lastSpike;
	Time currentTime;
	
	bool isRefractory();
	void updatePotential(const double& extI);
};

#endif // NEURON_H
