#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>
#include "constants.h"
#include "neuron.h"

class Neuron;

class Simulation {
public :
	Simulation();
	Simulation(const Time& simulationTime, const std::string& storeName);

	Time getCurrentTime() const;

	void simulateANeuron(const double& extI, const Time& extIBeginning, const Time& extIEnd);
	void simulateTwoNeurons(const double& extI, const Time& extIBeginning, const Time& extIEnd);

private :	
	Time currentTime_;
	const Time simulationTime_;
	std::string storingFile_;
	
	bool isInInterval(Time toTest, Time min, Time max);
	void storeInFile(double toStore, std::ofstream& out);
	void storeInFile(const std::vector<Neuron*>& neurons, std::ofstream& out);
	void initNeurons(std::vector<Neuron*>& neurons, size_t nb);

};

#endif // SIMULATION_H
