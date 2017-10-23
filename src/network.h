#ifndef NETWORK_H
#define NETWORK_H

#include <unordered_map>
//~ #include <vector>
#include <array>
#include "neuron.h"
#include "constants.h"

class Network {
public :
	Network();
	~Network();
	//~ void addNeuron(Neuron*, std::vector<Neuron*>);
	void addNeuron(Neuron*, std::array<Neuron*, (constants::CE + constants::CI)>);
	
private :
	//~ std::unordered_map<Neuron*, std::vector<Neuron*>> network_;
	std::unordered_map<Neuron*, std::array<Neuron*, (constants::CE + constants::CI)>> network_;
};



#endif // NETWORK_H
