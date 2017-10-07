#include "neuron.h"
#include "constants.h"
#include <iostream>
#include <vector>
#include <cmath>

Neuron::Neuron()
	: mbPotential(0.0), nextPotential(0.0), spikes({}) {}

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
	if (!spikes.empty()) {
		return currentTime <= (spikes.back()+constants::REFRACTORY_TIME);
	} else {
		return false;
	}
}


void Neuron::update(const Time& currentTime, const double& extI) {
	mbPotential = nextPotential;
	if (isRefractory(currentTime)) {
		mbPotential = 0.0;
	} else if(mbPotential >= constants::SPIKE_THRESHOLD) {
		mbPotential = constants::SPIKE_THRESHOLD;
		spikes.push_back(currentTime);
	}
		updatePotential(extI);
	//~ } else if (mbPotential < constants::SPIKE_THRESHOLD-0.00009) {
		//~ updatePotential(extI);
		//~ if (mbPotential > constants::SPIKE_THRESHOLD) {
			//~ mbPotential = constants::SPIKE_THRESHOLD;
		//~ }
	//~ } else { 
		//~ spikes.push_back(currentTime);
		//~ mbPotential = constants::SPIKE_THRESHOLD;
	//~ }
}

void Neuron::updatePotential(const double& extI) {
	double factor(exp(-constants::H/constants::TAU));
	nextPotential = factor*mbPotential + extI*constants::MB_RESISTANCE/constants::TAU*(1-factor);
}
