#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include "constants.h"

class Simulation {
public :
	Simulation();
	Simulation(const Time& simulationTime, const std::string& storeName);

	Time getCurrentTime() const;
	double getFactor1() const;
	double getFactor2() const;

	void simulateANeuron(const double& extI, const Time& extIBeginning, const Time& extIEnd);
private :	
	Time currentTime_;
	const Time simulationTime_;
	std::string storingFile_;
	const double calculationFactor1_;
	const double calculationFactor2_;
	
	bool isInInterval(Time toTest, Time min, Time max);
	void storeInFile(double toStore, std::ofstream& out);

};

#endif // SIMULATION_H
