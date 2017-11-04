#include <random>
#include "Neuron.h"
#include "Constants.h"
#include "Simulation.h"

Neuron::Neuron(bool excitatory)
	: mbPotential(constants::RESET_POTENTIAL),
	  nbSpikes(0),
	  lastSpike(0),
	  currentTime(0),
	  excitatory(excitatory) {
		  for (auto& J:buffer) {
			  J=0.0;
		  }
		  //~ std::cout << refractoryStep << ' '  << mbResistance << ' ' << ODEFactor1  << ' ' << ODEFactor2 << std::endl;
	  }

Neuron::Neuron()
	: Neuron(true) {}

double Neuron::getMbPotential() const {
	return mbPotential;
}
	
	
unsigned int Neuron::getNbSpikes() const {
	return nbSpikes;
}

Time Neuron::getSpikeTime() const {
	return lastSpike;
}

Time Neuron::getCurrentTime() const {
	return currentTime;
}

Potential Neuron::getJ() const {
	if (excitatory) {
		return constants::JE;
	} else {
		return constants::JI;
	}
}

bool Neuron::isRefractory() {
	if (nbSpikes>0) {
		return currentTime < (lastSpike+refractoryStep);
	} else {
		return false;
	}
}

bool Neuron::update(const double& extI, const Time& stopTime, const double& noise) {
	bool spiked(false);
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
	return spiked;
}

bool Neuron::update(const double& extI, const Time& stopTime) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::poisson_distribution<int> d(constants::DISTRIBUTION);
	return update(extI, stopTime, d(gen)*constants::JE); // Pas sûr
}

bool Neuron::update(const Time& stopTime) {
	return update(0.0, stopTime);
}	

void Neuron::updatePotential(const double& extI, const Potential& J) {
	//~ std::cout << J << '\t';
	mbPotential = ODEFactor1*mbPotential + extI*ODEFactor2 + J;
}

void Neuron::receiveSpike(const Potential& amplitude, const Time& receptionTime) {
	buffer[inBuffer(receptionTime)]+=amplitude;
	//~ std::cout << inBuffer(currentTime) << '	' << inBuffer(receptionTime) << std::endl;
}

void Neuron::receiveSpike(const Neuron* neur, const Time& receptionTime) {
	receiveSpike(neur->getJ(), receptionTime);
}

unsigned int Neuron::inBuffer(const Time& time) const {
	return (time-1) % (buffer.size());
}
