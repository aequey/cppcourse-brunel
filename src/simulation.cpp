#include "simulation.h"
#include "constants.h"
#include "neuron.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

Simulation::Simulation()
	: Simulation(constants::SIM_TIME, "../res/potentials.txt") {}
	
Simulation::Simulation(const Time& simulationTime, const std::string& storeName)
	: currentTime_(0.0),
	  simulationTime_(simulationTime),
	  storingFile_(storeName),
	  calculationFactor1_(exp(-constants::H/constants::TAU)),
	  calculationFactor2_(constants::MB_RESISTANCE*(1-calculationFactor1_)) {
	assert(simulationTime>=0.0);
}

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

void Simulation::storeInFile(const std::vector<Neuron*>& neurons, std::ofstream& out) {
	for (const auto& neur:neurons) {
		out << neur->getMbPotential() << '\t';
	}
	out << '\n';
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
		neuron.update(currentImput, *this, currentTime_+constants::H);

		storeInFile(neuron.getMbPotential(), file);
		currentTime_ += constants::H;
	}
	file.close();
}


void Simulation::simulateTwoNeurons(const double& extI, const Time& extIBeginning, const Time& extIEnd) {
	std::vector<Neuron*> neurons;
	initNeurons(neurons, 2);
	std::cout << neurons.size();
	double currentImput(0.0);
	std::ofstream file;
	file.open(storingFile_);
	
	while (currentTime_ <= simulationTime_) {
		if (isInInterval(currentTime_, extIBeginning, extIEnd)) {
			currentImput = extI;
		} else {
			currentImput = 0.0;
		}
		for (auto& neur:neurons) {
			neur->update(currentImput, *this, currentTime_+constants::H);
		}
		storeInFile(neurons, file);
		currentTime_ += constants::H;
	}
	file.close();
	for(auto& neur:neurons) {
		delete neur;
		neur = nullptr;
	}
	neurons.clear();
}

void Simulation::initNeurons(std::vector<Neuron*>& neurons, size_t nb) {
	assert(neurons.size()==0);
	for(size_t i(0); i<nb; ++i) {
		neurons.push_back(new Neuron);
		assert(neurons[i]->getMbPotential()==constants::RESET_POTENTIAL);
	}
	assert(neurons.size()==nb);
}
