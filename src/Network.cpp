#include <vector>
#include <fstream>
#include <random>
#include <cassert>

#include "Neuron.h"
#include "Network.h"


Network::Network() {
	network.clear();
	toSend.clear();
}

////////////////////////////////////////////////////////////////////////

void Network::generateConnexions(const std::vector<Neuron*>& neurons) {
	assert(neurons.size()==constants::NE+constants::NI);
	assert(constants::NE+constants::NI==constants::N_TOTAL);
	
	// Creating random distributios for random input connexions
	std::uniform_int_distribution<> distribE(0, constants::NE - 1);
	std::uniform_int_distribution<> distribI(constants::NE, neurons.size() - 1);
	std::random_device rd;
	std::mt19937 gen(rd());
	
	std::array<Neuron*, (constants::CE + constants::CI)> connexions;
	for (auto& n:neurons) {
		assert(n!=nullptr);
		connexions.fill(nullptr);
		// Create excitatory input connexions
		for (size_t i(0); i<constants::CE; ++i) {
			connexions[i] = neurons[distribE(gen)];
			assert(connexions[i]!=nullptr);
		}
		// Create inhibitory input connexions
		for (size_t i(constants::CE); i<connexions.size(); ++i) {
			connexions[i] = neurons[distribI(gen)];
			assert(connexions[i]!=nullptr);
		}
		// Add the neuron to the map of input connexions
		addNeuron(n, connexions);
	}
	// Create the map of output connexions from input connexions
	generateSenders(neurons);
}

////////////////////////////////////////////////////////////////////////

void Network::sendSpike(Neuron*& neur) const {
	assert(neur!=nullptr);
	Potential J(neur->getJ());
	Time t(neur->getCurrentTime());
	// Send the spike to all Neurons in output connexions
	for(auto& n:(toSend.at(neur))) {
		assert(n!=nullptr);
		n->receiveSpike(J, t+constants::D_IN_STEP);
	}
}

////////////////////////////////////////////////////////////////////////


void Network::generateSenders(const std::vector<Neuron*>& neurons) {
	std::vector<Neuron*> send;
	// First assign a vector of size 0 to enevy Neuron
	for (auto& n:neurons) {
		assert(n!=nullptr);
		send.clear();
		assert(send.size()==0);
		addNeuron(n, send);
	}
	// Fill this vector with output connexions got from input connexions
	for (auto& n:neurons) {
		for(auto& c:network[n]) {
			assert(c!=nullptr);
			toSend[c].push_back(n);
		}
	}
}

////////////////////////////////////////////////////////////////////////

void Network::addNeuron(Neuron* neuron, const std::array<Neuron*, (constants::CE + constants::CI)>& connexions) {
	assert(neuron!=nullptr);
	std::pair<Neuron*, std::array<Neuron*, (constants::CE + constants::CI)>> connexion(neuron, connexions);
	network.insert(connexion);
}

////////////////////////////////////////////////////////////////////////

void Network::addNeuron(Neuron* neuron, const std::vector<Neuron*>& connexions) {
	assert(neuron!=nullptr);
	std::pair<Neuron*, std::vector<Neuron*>> connexion(neuron, connexions);
	toSend.insert(connexion);
}
