#include "neuron.h"
#include "constants.h"
#include "simulation.h"
#include <vector>


Neuron::Neuron()
	: mbPotential(constants::RESET_POTENTIAL),
	  nextPotential(constants::RESET_POTENTIAL), 
	  spikes({}) {}

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

void Neuron::update(const double& extI, const Simulation& sim) {
	Time currentTime(sim.getCurrentTime());
	mbPotential = nextPotential;
	if (isRefractory(currentTime)) {
		mbPotential = constants::RESET_POTENTIAL;
	} else if(mbPotential > constants::SPIKE_THRESHOLD) {
		mbPotential = constants::SPIKE_THRESHOLD;
		spikes.push_back(currentTime);
	}
		updatePotential(extI, sim);
}

void Neuron::updatePotential(const double& extI, const Simulation& sim) {
	nextPotential = sim.getFactor1()*mbPotential + extI*sim.getFactor2();
}
