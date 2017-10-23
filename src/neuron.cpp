#include <random>
#include "neuron.h"
#include "constants.h"
#include "simulation.h"

Neuron::Neuron()
	: mbPotential(constants::RESET_POTENTIAL),
	  nbSpikes(0),
	  lastSpike(0),
	  currentTime(0) {
		  for (auto& J:buffer) {
			  J=0.0;
		  }
	  }

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
	Potential J(buffer[inBuffer(currentTime)]);
	bool spiked(false);
	while (currentTime<stopTime) {
		if (mbPotential>constants::SPIKE_THRESHOLD) {
			lastSpike = currentTime;
			++nbSpikes;
			spiked = true;
		}
		if (isRefractory()) {
			mbPotential=0.0;
		} else {
			updatePotential(extI, J);
		}
		buffer[inBuffer(currentTime)]=0.0;
		++currentTime;
	}
	return spiked;
}

void Neuron::updatePotential(const double& extI, const Potential& J) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::poisson_distribution<int> d(constants::CE*constants::H*0.02);
	mbPotential = ODEFactor1*mbPotential + extI*ODEFactor2 + J + d(gen)*0.1;
}

void Neuron::receiveSpike(const Potential& amplitude, const Time& delay) {
	buffer[inBuffer(currentTime+delay)]+=amplitude;
}

unsigned int Neuron::inBuffer(const Time& time) const {
	return time % (buffer.size());
}
