#include "simulation.h"
#include "constants.h"
#include "neuron.h"
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


//~ void Simulation::simulateTwoNeurons(const double& extI, const Time& extIBeginning, const Time& extIEnd) {
	//~ std::vector<Neuron*> neurons;
	//~ initNeurons(neurons, 2);
	
	//~ double currentImput(0.0);
	
	//~ std::ofstream file;
	//~ file.open(storingFile_);
	
	//~ while (currentTime_ <= simulationTime_) {
		//~ if (isInInterval(currentTime_, extIBeginning, extIEnd)) {
			//~ currentImput = extI;
		//~ } else {
			//~ currentImput = 0.0;
		//~ }
		//~ for (auto& neur:neurons) {
			//~ if (neur->update(currentImput, currentTime_+1)) {
				//~ for (auto& neuron:neurons) {
					//~ if (neuron != neur) {
						//~ neuron->receiveSpike(constants::J);
					//~ }
				//~ }
			//~ }
		//~ }
		//~ storeInFile(neurons, file);
		//~ ++currentTime_;
	//~ }
	//~ file.close();
	//~ for(auto& neur:neurons) {
		//~ delete neur;
		//~ neur = nullptr;
	//~ }
	//~ neurons.clear();
//~ }

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
			n2.receiveSpike(constants::JE, constants::D_IN_STEP);
		}
		n2.update(0.0, currentTime_+1);
		
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
