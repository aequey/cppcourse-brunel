#include <random>
#include "Neuron.h"
#include "Constants.h"
#include "Simulation.h"

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

Potential Neuron::getJ() const {
	return constants::JE;
}

bool Neuron::isRefractory() {
	if (nbSpikes>0) {
		return currentTime < (lastSpike+refractoryStep);
	} else {
		return false;
	}
}

bool Neuron::update(const double& extI, const Time& stopTime, const double& noise) {
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
			updatePotential(extI, J, noise);
		}
		buffer[inBuffer(currentTime)]=0.0;
		++currentTime;
	}
	return spiked;
}

bool Neuron::update(const double& extI, const Time& stopTime) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::poisson_distribution<int> d(2.0*constants::SPIKE_THRESHOLD/constants::TAU);
	return update(extI, stopTime, d(gen)*constants::H);
}

bool Neuron::update(const Time& stopTime) {
	return update(0.0, stopTime);
}	

void Neuron::updatePotential(const double& extI, const Potential& J, const double& noise) {
	mbPotential = ODEFactor1*mbPotential + extI*ODEFactor2 + J + noise;
}

void Neuron::receiveSpike(const Potential& amplitude, const Time& delay) {
	buffer[inBuffer(currentTime+delay)]+=amplitude;
}

void Neuron::receiveSpike(const Neuron* neur, const Time& delay) {
	receiveSpike(neur->getJ(), delay);
}

Potential Neuron::getJToExcitatory() const {
	return getJ();
}

unsigned int Neuron::inBuffer(const Time& time) const {
	return time % (buffer.size());
}
