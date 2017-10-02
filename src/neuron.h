#ifndef NEURON_H
#define NEURON_H

#include "constants.h"
#include <iostream>
#include <vector>

class Neuron {
public :
	Neuron();
	~Neuron() = default;
	
	void update(const Time& dt);
	double getMbPotential() const;
	size_t getNbSpikes() const;
	std::vector<double> getSpikeTimes() const;
private :
	double mbPotential;
	std::vector<double> spikes;
};

#endif // NEURON_H
