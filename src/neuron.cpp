#include "neuron.h"
#include "constants.h"
#include <iostream>
#include <vector>
#include <cmath>

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

bool Neuron::isRefractory(const Time& currentTime) {
	return currentTime < (spikes.back()+constants::REFRACTORY_TIME);
}


void Neuron::update(const Time& currentTime) {
	if (isRefractory(currentTime)) {
		mbPotential = 0.0;
	} else if (mbPotential > constants::SPIKE_THRESHOLD) {
		spikes.push_back(currentTime);
	}
	//~ updatePotential();
}

//~ void Neuron::updatePotential() {
	//~ exp(-constants::H/constants::TAU)*mbPotential + extI*constants::MB_RESISTANCE/constants::TAU*(1-exp())
//~ }
