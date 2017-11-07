#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <string>

#include "Constants.h"
#include "Neuron.h"


// predeclaration of class Neuron
class Neuron;

class Simulation;///< the class that manages the simulations. It allows to simulate one Neuron, two neurons or the complete Network with parameters given in Constants.h

class Simulation {
public :

	/*!
	 * @brief default constructor of Simulation
	 * @brief by default, the simulation time is given in constants::SIM_TIME and the data file is ../res/data.dat
	 * @param nothing
	 */
	Simulation();

	/*!
	 * @brief constructor of Simulation that allows to choose the time of the Simulation and the file where the data will be written
	 * @param the wanted simulation time and the name of the file we want the data inside
	 */
	Simulation(const Milliseconds& simulationTime, const std::string& storeName);

	/*!
	 * @brief default destructor of Simulation
	 */
	~Simulation() = default;

	/*!
	 * @brief gives the time of the Simulation
	 * @param nothing
	 * @return the time of the Simulation
	 */
	Time getCurrentTime() const;

	/*!
	 * @brief simulate a Neuron with a given external current that comes in a given interval of time 
	 * @param the external current, and the beginning and end if the time interval
	 * @return void
	 */
	void simulateANeuron(const double& extI, const Milliseconds& extIBeginning, const Milliseconds& extIEnd);

	/*!
	 * @brief simulate two neurons and one connexion. The first one receives a given current during a given time interval
	 * @param the external current for the first Neuron, and the beginning and end if the time interval
	 * @return void
	 */
	void simulateTwoNeurons(const double& extI, const Milliseconds& extIBeginning, const Milliseconds& extIEnd);

	/*!
	 * @brief simulate the whole network of neurons according to Brunel's model and the constants file. There is no external current
	 * @param nothong
	 * @return void
	 */
	void simulateNetwork();
	
private :	
	Time currentTime;			///< the Time it is currently in the Simulation
	const Time simulationTime;	///< the total Time of the Simulation
	std::string storingFile;	///< the name of the file we want to store the data in
	
	static constexpr Time totalStep = (constants::SIM_TIME/constants::H);	///< the conversion of default simulation time into steps
	
	/*!
	 * @brief utilitary method that tells if a given time is between two given bounds
	 * @param the Time we want to test (in simulation Time) and the bounds (in Milliseconds)
	 * @return true if the time to test is in the interval, false if not
	 */
	bool isInInterval(Time toTest, Milliseconds min, Milliseconds max);

};

#endif // SIMULATION_H
