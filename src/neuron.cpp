#include "neuron.h"
#include "constants.h"
#include "simulation.h"
#include <vector>
//~ #include <iostream>

Neuron::Neuron()
	: mbPotential(constants::RESET_POTENTIAL),
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
	while (currentTime<stopTime) {
		if (mbPotential>constants::SPIKE_THRESHOLD) {
			lastSpike = currentTime;
			++nbSpikes;
		}
		if (isRefractory()) {
			mbPotential=0.0;
		} else {
			updatePotential(extI);
		}
		currentTime+=constants::H;	
	}	
}

void Neuron::updatePotential(const double& extI) {
	mbPotential = ODEFactor1*mbPotential + extI*ODEFactor2 + nextJ;
	nextJ = 0.0;
}

void Neuron::receiveSpike(const double& amplitude) {
	nextJ+=amplitude;
}
