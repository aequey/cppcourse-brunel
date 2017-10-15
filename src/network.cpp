#include "network.h"
#include "neuron.h"
#include <vector>

Network::Network() {
	network_.clear();
}

Network::~Network() {
	for (auto connexions(network_.begin()); connexions!=network_.end();++connexions) {
		for (auto& neuron:connexions->second) {
			delete neuron;
		}
		delete connexions->first;
	}
}

void Network::addNeuron(Neuron* neuron, std::vector<Neuron*> connexions) {
	std::pair<Neuron*, std::vector<Neuron*>> connexion(neuron, connexions);
	network_.insert(connexion);
}
