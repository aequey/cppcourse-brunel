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
	
	void update(const double& extI, const Simulation& sim);
	double getMbPotential() const;
	size_t getNbSpikes() const;
	std::vector<Time> getSpikeTimes() const;
private :
	double mbPotential;
	double nextPotential;
	std::vector<Time> spikes;
	
	bool isRefractory(const Time& currentTime);
	void updatePotential(const double& extI, const Simulation& sim);
};

#endif // NEURON_H
