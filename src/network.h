#ifndef NETWORK_H
#define NETWORK_H

#include <unordered_map>
#include <vector>
#include "neuron.h"

class Network {
public :
	Network();
	~Network();
	void addNeuron(Neuron*, std::vector<Neuron*>);
private :
	std::unordered_map<Neuron*, std::vector<Neuron*>> network_;
};



#endif // NETWORK_H
