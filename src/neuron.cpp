#include "neuron.h"
#include "constants.h"
#include <iostream>
#include <vector>

Neuron::Neuron()
	: mbPotential(0.0), spikes({}) {}

double Neuron::getMbPotential() const {
	return mbPotential;
}
	
size_t Neuron::getNbSpikes() const {
	return spikes.size();
}

std::vector<double> Neuron::getSpikeTimes() const {
	return spikes;
}


void Neuron::update(const Time& dt) {}
