#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>
#include "Constants.h"
#include "Neuron.h"

///< the class that manages the simulations.
///< It allows to simulate one Neuron, two neurons or the complete Network with parameters given in Constants.h


class Neuron; ///< predeclaration of class Neuron


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
	 * @brief gives the time of the Simulation
	 * @param nothing
	 * @return the time of the Simulation
	 */
	Time getCurrentTime() const;

	/*!
	 * @brief 
	 * @param 
	 * @return 
	 */
	void simulateANeuron(const double& extI, const Milliseconds& extIBeginning, const Milliseconds& extIEnd);

	/*!
	 * @brief 
	 * @param 
	 * @return 
	 */
	void simulateTwoNeurons(const double& extI, const Milliseconds& extIBeginning, const Milliseconds& extIEnd);

	/*!
	 * @brief 
	 * @param 
	 * @return 
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

	/*!
	 * @brief utilitary method that allows to store in an ofstream a given number
	 * @param the number to store and the ofstream
	 * @return void
	 */
	void storeInFile(double toStore, std::ofstream& out);

	/*!
	 * @brief utilitary method that allows to store in an ofstream the potentials of a group of eurons
	 * @param the vectorss of neurons (pointers) and the ofstream
	 * @return void
	 */
	void storeInFile(const std::vector<Neuron*>& neurons, std::ofstream& out);

};

#endif // SIMULATION_H
