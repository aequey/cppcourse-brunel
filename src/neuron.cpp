#include "neuron.h"
#include "constants.h"
#include "simulation.h"
#include <vector>
#include <iostream>

Neuron::Neuron()
	: mbPotential(constants::RESET_POTENTIAL),
	  nbSpikes(0),
	  lastSpike(0.0),
	  currentTime(0.0) {}

double Neuron::getMbPotential() const {
	return mbPotential;
}
	
	
unsigned int Neuron::getNbSpikes() const {
	return nbSpikes;
}

Time Neuron::getSpikeTime() const {
	return lastSpike;
}


bool Neuron::isRefractory(const Time& currentTime) {
	if (nbSpikes>0) {
		return currentTime < (lastSpike+constants::REFRACTORY_TIME);
	} else {
		return false;
	}
}

void Neuron::update(const double& extI, const Simulation& sim, const Time& stopTime) {
	while (currentTime<stopTime) {
		if (!(mbPotential<constants::SPIKE_THRESHOLD)) {
			lastSpike = currentTime;
			++nbSpikes;
		}
		if (isRefractory(currentTime)) {
			mbPotential=0.0;
		} else {
			updatePotential(extI, sim);
		}
		currentTime+=constants::H;	
	}	
}

void Neuron::updatePotential(const double& extI, const Simulation& sim) {
	mbPotential = sim.getFactor1()*mbPotential + extI*sim.getFactor2();
	if (mbPotential>constants::SPIKE_THRESHOLD) {
		mbPotential=constants::SPIKE_THRESHOLD;
	}
}
