#include "network.h"
#include "neuron.h"
#include <vector>
#include <random>
#include <iostream>

Network::Network() {
	network.clear();
	toSend.clear();
}

Network::~Network() {
	for (auto connexions(network.begin()); connexions!=network.end();++connexions) {
		for (auto& neuron:connexions->second) {
			delete neuron;
		}
		delete connexions->first;
	}
	for (auto connexions(toSend.begin()); connexions!=toSend.end();++connexions) {
		for (auto& neuron:connexions->second) {
			delete neuron;
		}
		delete connexions->first;
	}

}

void Network::addNeuron(Neuron* neuron, std::array<Neuron*, (constants::CE + constants::CI)> connexions) {
	std::pair<Neuron*, std::array<Neuron*, (constants::CE + constants::CI)>> connexion(neuron, connexions);
	network.insert(connexion);
}

void Network::addNeuron(Neuron* neuron, std::vector<Neuron*> connexions) {
	std::pair<Neuron*, std::vector<Neuron*>> connexion(neuron, connexions);
	toSend.insert(connexion);
}

void Network::generateConnexions(const std::vector<Neuron*>& neurons) {
	assert(neurons.size()==constants::NE+constants::NI);
	//~ size_t i(0);
	std::uniform_int_distribution<> distribE(0, constants::CE - 1);
	std::uniform_int_distribution<> distribI(constants::CE, neurons.size());
	for (auto& n:neurons) {
		//~ std::cout << i << std:: endl;
		//~ ++i;
		std::array<Neuron*, (constants::CE + constants::CI)> connexions;
		//~ std::cout << connexions.size() << std::endl;
		for (size_t i(0); i<constants::CE; ++i) {
			//~ std::cout << i << std::endl;
			std::random_device rd;
			std::mt19937 gen(rd());
			connexions[i] = neurons[distribE(gen)];
		}
		for (size_t i(constants::CE); i<connexions.size(); ++i) {
			std::random_device rd;
			std::mt19937 gen(rd());
			connexions[i] = neurons[distribI(gen)];
		}
		//~ std::cout << "OK" << std::endl;
		addNeuron(n, connexions);
	}
}

void Network::generateSenders(std::vector<Neuron*> neurons) {
	for (auto& n:neurons) {
		std::vector<Neuron*> send;
		addNeuron(n, send);
	}
	
	for (auto& n:neurons) {
		for(auto& c:network[n]) {
			toSend[c].push_back(n);
		}
	}
}


void Network::sendSpike(Neuron*& neur) const {
	for(auto& n:toSend.at(neur)) {
		n->receiveSpike(constants::JE, constants::D_IN_STEP);
	}
}
