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
	std::vector<Time> getSpikeTimes() const;
private :
	double mbPotential;
	std::vector<Time> spikes;
	
	bool isRefractory(const Time& currentTime);
	//~ void updatePotential();
};

#endif // NEURON_H
