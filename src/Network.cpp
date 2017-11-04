#include "Network.h"
#include "Neuron.h"
#include <vector>
#include <random>
#include <fstream>
#include <cassert>

Network::Network() {
	network.clear();
	toSend.clear();
}

void Network::addNeuron(Neuron* neuron, const std::array<Neuron*, (constants::CE + constants::CI)>& connexions) {
	assert(neuron!=nullptr);
	std::pair<Neuron*, std::array<Neuron*, (constants::CE + constants::CI)>> connexion(neuron, connexions);
	network.insert(connexion);
}

void Network::addNeuron(Neuron* neuron, const std::vector<Neuron*>& connexions) {
	assert(neuron!=nullptr);
	std::pair<Neuron*, std::vector<Neuron*>> connexion(neuron, connexions);
	toSend.insert(connexion);
}

void Network::generateConnexions(const std::vector<Neuron*>& neurons) {
	assert(neurons.size()==constants::NE+constants::NI);
	assert(constants::NE+constants::NI==constants::N_TOTAL);
	
	std::uniform_int_distribution<> distribE(0, constants::NE - 1);
	std::uniform_int_distribution<> distribI(constants::NE, neurons.size() - 1);
	std::random_device rd;
	std::mt19937 gen(rd());
	
	std::array<Neuron*, (constants::CE + constants::CI)> connexions;
	for (auto& n:neurons) {
		connexions.fill(nullptr);
		for (size_t i(0); i<constants::CE; ++i) {
			connexions[i] = neurons[distribE(gen)];
			assert(connexions[i]!=nullptr);
		}
		for (size_t i(constants::CE); i<connexions.size(); ++i) {
			connexions[i] = neurons[distribI(gen)];
			assert(connexions[i]!=nullptr);
		}
		addNeuron(n, connexions);
	}
	generateSenders(neurons);
}

void Network::generateSenders(const std::vector<Neuron*>& neurons) {
	std::vector<Neuron*> send;
	for (auto& n:neurons) {
		send.clear();
		assert(send.size()==0);
		addNeuron(n, send);
	}
	for (auto& n:neurons) {
		for(auto& c:network[n]) {
			assert(c!=nullptr);
			toSend[c].push_back(n);
		}
	}
}


void Network::sendSpike(Neuron*& neur) const {
	Potential J(neur->getJ());
	Time t(neur->getCurrentTime());
	for(auto& n:(toSend.at(neur))) {
	assert(n!=nullptr);
		n->receiveSpike(J, t+constants::D_IN_STEP);
	}
}
