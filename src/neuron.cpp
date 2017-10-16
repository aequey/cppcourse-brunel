#include "neuron.h"
#include "constants.h"
#include "simulation.h"
#include <vector>

Neuron::Neuron()
	: mbPotential(constants::RESET_POTENTIAL),
	  J(0.0),
	  nbSpikes(0),
	  lastSpike(0),
	  currentTime(0) {}

double Neuron::getMbPotential() const {
	return mbPotential;
}
	
	
unsigned int Neuron::getNbSpikes() const {
	return nbSpikes;
}

Time Neuron::getSpikeTime() const {
	return lastSpike;
}


bool Neuron::isRefractory() {
	if (nbSpikes>0) {
		return currentTime < (lastSpike+refractoryStep);
	} else {
		return false;
	}
}

bool Neuron::update(const double& extI, const Time& stopTime) {
	bool spike(false);
	while (currentTime<stopTime) {
		if (mbPotential>constants::SPIKE_THRESHOLD) {
			lastSpike = currentTime;
			++nbSpikes;
			spike = true;
		}
		if (isRefractory()) {
			mbPotential=0.0;
		} else {
			updatePotential(extI);
		}
		++currentTime;	
	}
	return spike;
}

void Neuron::updatePotential(const double& extI) {
	mbPotential = ODEFactor1*mbPotential + extI*ODEFactor2 + J;
	J = 0.0;
}

void Neuron::receiveSpike(const double& amplitude) {
	J+=amplitude;
}
