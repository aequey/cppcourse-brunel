#ifndef NEURON_H
#define NEURON_H

#include "constants.h"
#include <iostream>
#include <vector>

class Neuron {
public :
	Neuron();
	~Neuron() = default;
	
	void update(const Time& dt, const double& extI);
	double getMbPotential() const;
	size_t getNbSpikes() const;
	std::vector<Time> getSpikeTimes() const;
private :
	double mbPotential;
	double nextPotential;
	std::vector<Time> spikes;
	
	bool isRefractory(const Time& currentTime);
	void updatePotential(const double& extI);
};

#endif // NEURON_H
