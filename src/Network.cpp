#include "Network.h"
#include "Neuron.h"
#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <cassert>

Network::Network() {
	network.clear();
	toSend.clear();
}

Network::~Network() {
	//~ for (auto connexions(network.begin()); connexions!=network.end();++connexions) {
		//~ for (auto& neuron:connexions->second) {
			//~ delete neuron;
		//~ }
		//~ delete connexions->first;
	//~ }
	//~ for (auto connexions(toSend.begin()); connexions!=toSend.end();++connexions) {
		//~ for (auto& neuron:connexions->second) {
			//~ delete neuron;
		//~ }
		//~ delete connexions->first;
	//~ }

}

void Network::addNeuron(Neuron* neuron, const std::array<Neuron*, (constants::CE + constants::CI)>& connexions) {
	std::pair<Neuron*, std::array<Neuron*, (constants::CE + constants::CI)>> connexion(neuron, connexions);
	network.insert(connexion);
}

void Network::addNeuron(Neuron* neuron, const std::vector<Neuron*>& connexions) {
	std::pair<Neuron*, std::vector<Neuron*>> connexion(neuron, connexions);
	toSend.insert(connexion);
}

void Network::generateConnexions(const std::vector<Neuron*>& neurons) {
	assert(neurons.size()==constants::NE+constants::NI);
	
	std::uniform_int_distribution<> distribE(0, constants::NE - 1);
	std::uniform_int_distribution<> distribI(constants::NE, neurons.size());
	std::random_device rd;
	std::mt19937 gen(rd());
	
	std::array<Neuron*, (constants::CE + constants::CI)> connexions;

	for (auto& n:neurons) {
		for (size_t i(0); i<constants::CE; ++i) {
			connexions[i] = neurons[distribE(gen)];
		}
		for (size_t i(constants::CE); i<connexions.size(); ++i) {
			connexions[i] = neurons[distribI(gen)];
		}
		addNeuron(n, connexions);
	}
}

void Network::generateSenders(const std::vector<Neuron*>& neurons) {
	std::vector<Neuron*> send;
	for (auto& n:neurons) {
		addNeuron(n, send);
		for(auto& c:network[n]) {
			toSend[c].push_back(n);
		}
	}
	
	//~ for (auto& n:neurons) {
		//~ }
	//~ }
}


void Network::sendSpike(Neuron*& neur) const {
	for(auto& n:toSend.at(neur)) {
		n->receiveSpike(neur->getJ(), constants::D_IN_STEP);
	}
}


//~ void Network::printConnexions(std::ofstream& file) {
	//~ for (auto connexions(toSend.begin()); connexions!=toSend.end();++connexions) {
		//~ for (const auto& neuron:connexions->second)
		//~ file << neuron << '\t';
	//~ }
	//~ file << std::endl << std::endl;
//~ }
