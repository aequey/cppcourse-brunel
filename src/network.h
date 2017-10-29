#ifndef NETWORK_H
#define NETWORK_H

#include <unordered_map>
#include <vector>
//~ #include <array>
#include "neuron.h"
#include "constants.h"

class Network {
public :
	Network();
	~Network();
	void generateConnexions(const std::vector<Neuron*>& neurons);
	void generateSenders(std::vector<Neuron*> neurons);
	void addNeuron(Neuron*, std::vector<Neuron*>);
	void addNeuron(Neuron*, std::array<Neuron*, (constants::CE + constants::CI)>);
	void sendSpike(Neuron*& neur) const;
private :
	std::unordered_map<Neuron*, std::vector<Neuron*>> toSend;
	std::unordered_map<Neuron*, std::array<Neuron*, (constants::CE + constants::CI)>> network;
};



#endif // NETWORK_H
