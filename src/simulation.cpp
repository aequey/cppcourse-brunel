#include "simulation.h"
#include "constants.h"
#include "neuron.h"
#include <fstream>
#include <cmath>

Simulation::Simulation()
	: Simulation(constants::SIM_TIME, "../res/potentials.txt") {}
	
Simulation::Simulation(const Time& simulationTime, const std::string& storeName)
	: currentTime_(0.0),
	  simulationTime_(simulationTime),
	  storingFile_(storeName),
	  calculationFactor1_(exp(-constants::H/constants::TAU)),
	  calculationFactor2_(constants::MB_RESISTANCE*(1-calculationFactor1_)) {}

Time Simulation::getCurrentTime() const {
	return currentTime_;
}

double Simulation::getFactor1() const {
	return calculationFactor1_;
}
double Simulation::getFactor2() const {
	return calculationFactor2_;
}

bool Simulation::isInInterval(Time toTest, Time min, Time max) {
	return (toTest >= min and toTest < max);
}

void Simulation::storeInFile(double toStore, std::ofstream& out) {
	out << toStore <<std::endl;
}

void Simulation::simulateANeuron(const double& extI, const Time& extIBeginning, const Time& extIEnd) {
	Neuron neuron;
	double currentImput(0.0);
	std::ofstream file;
	file.open(storingFile_);
	while (currentTime_ <= simulationTime_) {
		if (isInInterval(currentTime_, extIBeginning, extIEnd)) {
			currentImput = extI;
		} else {
			currentImput = 0.0;
		}
		neuron.update(currentImput, *this);

		storeInFile(neuron.getMbPotential(), file);
		currentTime_ += constants::H;
	}
	file.close();
}
