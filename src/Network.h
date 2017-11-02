#ifndef NETWORK_H
#define NETWORK_H

#include <unordered_map>
#include <vector>
#include <array>
#include <fstream>
#include "Neuron.h"
#include "Constants.h"

class Network {
public :
	Network();
	~Network();
	void generateConnexions(const std::vector<Neuron*>& neurons);
	void generateSenders(const std::vector<Neuron*>& neurons);
	void addNeuron(Neuron*, const std::vector<Neuron*>&);
	void addNeuron(Neuron*, const std::array<Neuron*, (constants::CE + constants::CI)>&);
	void sendSpike(Neuron*& neur) const;
	
	//~ void printConnexions(std::ofstream& file);

private :
	std::unordered_map<Neuron*, std::vector<Neuron*>> toSend;
	std::unordered_map<Neuron*, std::array<Neuron*, (constants::CE + constants::CI)>> network;
};



#endif // NETWORK_H
