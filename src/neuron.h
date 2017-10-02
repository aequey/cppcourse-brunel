#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>

class Neuron {
public :
	Neuron();
	~Neuron() = default;
private :
	double mbPotential;
	std::vector<double> spikes;
};

#endif // NEURON_H
