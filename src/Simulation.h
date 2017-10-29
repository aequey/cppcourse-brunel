#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>
#include "Constants.h"
#include "Neuron.h"

class Neuron;

class Simulation {
public :
	Simulation();
	Simulation(const Milliseconds& simulationTime, const std::string& storeName);

	Time getCurrentTime() const;

	void simulateANeuron(const double& extI, const Milliseconds& extIBeginning, const Milliseconds& extIEnd);
	void simulateTwoNeurons(const double& extI, const Milliseconds& extIBeginning, const Milliseconds& extIEnd);
	void simulateNetwork();
	
private :	
	Time currentTime_;
	const Time simulationTime_;
	std::string storingFile_;
	
	static constexpr Time totalStep = (constants::SIM_TIME/constants::H);
	
	bool isInInterval(Time toTest, Milliseconds min, Milliseconds max);
	void storeInFile(double toStore, std::ofstream& out);
	void storeInFile(const std::vector<Neuron*>& neurons, std::ofstream& out);
	void initNeurons(std::vector<Neuron*>& neurons, size_t nb);

};

#endif // SIMULATION_H
