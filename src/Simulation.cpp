#include "Simulation.h"
#include "Constants.h"
//~ #include "Neuron.h"
#include "ExcitatoryNeuron.h"
#include "InhibitoryNeuron.h"
#include "Network.h"
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>

Simulation::Simulation()
	: Simulation(totalStep, "../res/potentials.txt") {}
	
Simulation::Simulation(const Milliseconds& simulationTime, const std::string& storeName)
	: currentTime_(0),
	  simulationTime_(simulationTime/constants::H),
	  storingFile_(storeName) {
		  
	  assert(simulationTime>=0);
}

Time Simulation::getCurrentTime() const {
	return currentTime_;
}

bool Simulation::isInInterval(Time toTest, Milliseconds min, Milliseconds max) {
	double test(toTest*constants::H);
	return (!(test < min) and test < max);
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

void Simulation::simulateANeuron(const double& extI, const Milliseconds& extIBeginning, const Milliseconds& extIEnd) {
	Neuron neuron;
	double currentImput(0.0);
	std::ofstream file;
	file.open(storingFile_);
	while (currentTime_ <= simulationTime_) {
		file << currentTime_*constants::H << '\t' << neuron.getMbPotential() << std::endl;
		if (isInInterval(currentTime_, extIBeginning, extIEnd)) {
			currentImput = extI;
		} else {
			currentImput = 0.0;
		}
		neuron.update(currentImput, currentTime_+1);

		++currentTime_;
	}
	file.close();
}

void Simulation::simulateTwoNeurons(const double& extI, const Milliseconds& extIBeginning, const Milliseconds& extIEnd) {
	Neuron n1;
	Neuron n2;
	
	double currentImput(0.0);
	
	std::ofstream file;
	file.open(storingFile_);

	
	while (currentTime_ <= simulationTime_) {
		file << currentTime_*constants::H << '\t' << n1.getMbPotential() << '\t' << n2.getMbPotential() << std::endl;
		if (isInInterval(currentTime_, extIBeginning, extIEnd)) {
			currentImput = extI;
		} else {
			currentImput = 0.0;
		}
		
		bool spike;
		spike = n1.update(currentImput, currentTime_+1);
		
		if (spike) {
			n2.receiveSpike(n1.getJ(), constants::D_IN_STEP);
		}
		n2.update(0.0, currentTime_+1);
		
		++currentTime_;

	}
	
	file.close();
}

void Simulation::simulateNetwork() {
	Network net;
	
	std::vector<Neuron*> neur;
	
	for (unsigned int i(0); i<constants::NE; ++i) {
		neur.push_back(new ExcitatoryNeuron);
	}
	
	for (unsigned int i(0); i<constants::NI; ++i) {
		neur.push_back(new InhibitoryNeuron);
	}
	
	std::cout << "Generating connexions..." << std::endl;
	net.generateConnexions(neur);
	std::cout << "Connexions generated" << std::endl;
	std::cout << "Generating senders..." << std::endl;
	net.generateSenders(neur);
	std::cout << "Senders generated" << std::endl;	
	
	std::ofstream file;
	file.open(storingFile_);

	std::cout << "Starting simulation..." << std::endl;
	while (currentTime_ <= simulationTime_) {
		//~ for (const auto& n:neur) {
			//~ file  << '\t' << n->getMbPotential();
		//~ }
		
		bool spike;
		//~ for (auto& n:neur) {
		for (size_t i(0); i<neur.size();++i) {
			spike = neur[i]->update(currentTime_+1);
		
			if (spike) {
				net.sendSpike(neur[i]);
					file << currentTime_*constants::H << '\t' << i;
					file << '\n';

			}
		}
		std::cout << currentTime_*0.1 << " ms" << std::endl;
		++currentTime_;

	}
	
	file.close();
}


void Simulation::initNeurons(std::vector<Neuron*>& neurons, size_t nb) {
	assert(neurons.size()==0);
	for(size_t i(0); i<nb; ++i) {
		neurons.push_back(new Neuron);
		assert(neurons[i]->getMbPotential()==constants::RESET_POTENTIAL);
	}
	assert(neurons.size()==nb);
}
