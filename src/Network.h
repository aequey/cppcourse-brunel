#ifndef NETWORK_H
#define NETWORK_H

#include <unordered_map>
#include <vector>
#include <array>
#include <fstream>
#include "Neuron.h"
#include "Constants.h"


///< a class that creates and manages the connexions between neurons.
///< we talk about a Network of neurons.


class Network {
public :

	/*!
	 * @brief the default constructor of the network
	 * @param nothing
	 */
	Network();
	
	/*!
	 * @brief the default constructor of the network
	 * @param nothing
	 */
	~Network();
	
	/*!
	 * @brief method that creates the input connexions between neurons from given neurons.
	 * @brief connexions are randomly generated (each neuron receives a given number of connexions from excitatory and inhibitory neurons)
	 * @brief the number of connexions of each neuron is given in Constants.h (CE excitatory, CI inhibitory)
	 * @param the group of Neuron (a vector) we want the input connexions to be generated
	 * @return void
	 */	
	void generateConnexions(const std::vector<Neuron*>& neurons);
	
	/*!
	 * @brief a method that calculates the connexions each Neuron sends from the connexions each Neuron receives.
	 * @brief this second version of the network is more efficient when a neuron has to send a spike to all its receivers.
	 * @param the group of Neuron (a vector) we want the output connexions to be generated
	 * @return void
	 */
	void generateSenders(const std::vector<Neuron*>& neurons);
	
	/*!
	 * @brief a method that takes a Neuron and send a spike to all its receivers.
	 * @param the Neuron we want to spike
	 * @return void
	 */
	void sendSpike(Neuron*& neur) const;
	
private :

	std::unordered_map<Neuron*, std::array<Neuron*, (constants::CE + constants::CI)>> network; ///< a map of neurons with their respective input connexions 
	std::unordered_map<Neuron*, std::vector<Neuron*>> toSend; ///< a map of neurons with their respective output connexions
	
	
	/*!
	 * @brief an utilitary method that adds a Neuron and its output connexions to the attribute Network::network
	 * @param the neuron and its output connexions
	 * @return void
	 */
	void addNeuron(Neuron*, const std::array<Neuron*, (constants::CE + constants::CI)>&);
	
	/*!
	 * @brief an utilitary method that adds a Neuron and its input connexions to the attribute Network::toSend
	 * @param The neuron and its input connexions
	 * @return void
	 */	
	void addNeuron(Neuron*, const std::vector<Neuron*>&);
};



#endif // NETWORK_H
