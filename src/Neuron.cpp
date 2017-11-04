#include <random>

#include "Constants.h"
#include "Neuron.h"


Neuron::Neuron()
	  // By default, a Neuron is excitatory
	: Neuron(true) {}

////////////////////////////////////////////////////////////////////////

Neuron::Neuron(bool excitatory)
	: mbPotential(constants::RESET_POTENTIAL),
	  nbSpikes(0),
	  lastSpike(0),
	  currentTime(0),
	  excitatory(excitatory) {
		  for (auto& J:buffer) {
			  J=0.0;
		  }
	  }

////////////////////////////////////////////////////////////////////////

double Neuron::getMbPotential() const {
	return mbPotential;
}
	
////////////////////////////////////////////////////////////////////////

Time Neuron::getSpikeTime() const {
	return lastSpike;
}

////////////////////////////////////////////////////////////////////////

unsigned int Neuron::getNbSpikes() const {
	return nbSpikes;
}

////////////////////////////////////////////////////////////////////////

Time Neuron::getCurrentTime() const {
	return currentTime;
}

////////////////////////////////////////////////////////////////////////

Potential Neuron::getJ() const {
	if (excitatory) {
		return constants::JE;
	} else {
		assert(constants::JI<0.0);
		return constants::JI;
	}
}

////////////////////////////////////////////////////////////////////////

bool Neuron::update(const double& extI, const Time& stopTime, const double& noise) {
	assert(stopTime>=currentTime);
	bool spiked(false);
	// We suppose the noise is the same for every step of the update (only one step in our simulations)
	while (currentTime<stopTime) {
		Potential J(buffer[inBuffer(currentTime)]+noise);
		buffer[inBuffer(currentTime)]=0.0;
		if (mbPotential>constants::SPIKE_THRESHOLD) {
			lastSpike = currentTime;
			++nbSpikes;
			spiked = true;
		}
		if (isRefractory()) {
			mbPotential=constants::RESET_POTENTIAL;
		} else {
			updatePotential(extI, J);
		}
		++currentTime;
	}
	assert(currentTime==stopTime);
	return spiked;
}

////////////////////////////////////////////////////////////////////////

bool Neuron::update(const double& extI, const Time& stopTime) {
	// Creation of random distribution for external spikes.
	// The same distribution is used for every neuron at every time of the simulation.
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::poisson_distribution<int> d(constants::DISTRIBUTION);
	// Update with a random number taken from this distribution as noise
	return update(extI, stopTime, d(gen)*constants::JE);
}

////////////////////////////////////////////////////////////////////////

bool Neuron::update(const Time& stopTime) {
	// update with no external current, but random spikes
	return update(0.0, stopTime);
}	

////////////////////////////////////////////////////////////////////////

void Neuron::receiveSpike(const Potential& amplitude, const Time& receptionTime) {
	assert(receptionTime>=currentTime);
	buffer[inBuffer(receptionTime)]+=amplitude;
}

////////////////////////////////////////////////////////////////////////

void Neuron::receiveSpike(const Neuron*& neur, const Time& receptionTime) {
	assert(neur!=nullptr);
	assert(receptionTime>=currentTime);
	// J is not the same if the Neuron is excitatory or inhibitory
	receiveSpike(neur->getJ(), receptionTime);
}

////////////////////////////////////////////////////////////////////////

bool Neuron::isRefractory() {
	if (nbSpikes>0) {
		return currentTime < (lastSpike+refractoryStep);
	} else {
		return false;
	}
}

////////////////////////////////////////////////////////////////////////

void Neuron::updatePotential(const double& extI, const Potential& J) {
	// This is the result of the differential equation.
	// Every input that comes from other neurons (spikes in buffer and noise) is in J
	mbPotential = ODEFactor1*mbPotential + extI*ODEFactor2 + J;
}

////////////////////////////////////////////////////////////////////////

unsigned int Neuron::inBuffer(const Time& time) const {
	// The equation given in lectures has not the -1, but it seems here to give a too big time.
	return (time-1) % (buffer.size());
}
