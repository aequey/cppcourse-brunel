#ifndef NEURON_H
#define NEURON_H

#include <array>

#include "Constants.h"


///< A class that represents a neuron.
///< They are two types of neurons : excitatory and inhibitory (the change is only in amplitude of the spike)


class Neuron {
public :

	/*!
	 * @brief default constructor of Neuron. By default, a Neuron is excitatory. calls Neuron::Neuron(true)
	 * @param nothing
	 */
	Neuron();
	
	/*!
	 * @brief constructor of Neuron that permits creation of excitatory or inhibitory Neuron
	 * @param a boolean : true if the Neuron will be excitatory, false if inhibitory
	 */
	Neuron(bool excitatory);

	/*!
	 * @brief default destructor of Neuron
	 */
	~Neuron() = default;

	/*!
	 * @brief returns the membrane potential
	 * @param nothing
	 * @return the membrane potential
	 */
	Potential getMbPotential() const;
	
	/*!
	 * @brief returns the time of the last spike of the Neuron
	 * @param nothing
	 * @return the time of the last spike of the neuron
	 */
	Time getSpikeTime() const;

	/*!
	 * @brief returns the number of spikes the Neuron has already had
	 * @param nothing
	 * @return the number of spikes
	 */
	unsigned int getNbSpikes() const;

	/*!
	 * @brief returns the time in the Neuron Referential
	 * @param nothing
	 * @return the time for the Neuron
	 */
	Time getCurrentTime() const;

	/*!
	 * @brief returns the amplitude of the spike the Neuron sends (depends wether it's excitatory or inhibitory)
	 * @param nothing
	 * @return the amplitude of the spike
	 */
	Potential getJ() const;

	/*!
	 * @brief update a Neuron until a given stopTime, with a given external current and given noise
	 * @param the external current, the stopTime and the noise
	 * @return true if the Neuron has spiked during the update time, false if not
	 */
	bool update(const double& extI, const Time& stopTime, const double& noise);
	
	/*!
	 * @brief update a Neuron with a given current until a given stopTime. Generates random noise from a Poisson distribution
	 * @param the external current and the stopTime
	 * @return true if the Neuron has spiked during the update time, false if not
	 */
	bool update(const double& extI, const Time& stopTime);

	/*!
	 * @brief update a Neuron until a given stopTime. There's no external current and the noise is randomly generated from a Poisson distribution
	 * @param the stopTime
	 * @return true if the Neuron has spiked during the update time, false if not
	 */
	bool update(const Time& stopTime);

	/*!
	 * @brief fills the buffer so that the Neuron receives a spike of a given amplitude at a given time
	 * @brief the time shall not exceed the current time + constants::D
	 * @param the amplitude of the spike and the time when it should arrive
	 * @return void
	 */
	void receiveSpike(const Potential& amplitude, const Time & receptionTime);

	/*!
	 * @brief fills the buffer so that the Neuron receives a spike from a given Neuron at a given time
	 * @brief this implementation allows to make a difference between excitatory or inhibitory Neuron
	 * @param the Neuron that sends the spike and the time when it should arrive
	 * @return void
	 */
	void receiveSpike(const Neuron*& neur, const Time& receptionTime);
	
private :

	Potential mbPotential;	///< the potential of the Neuron (in mV, if it reaches conatants::SPIKE_THRESHOLD, sends a spike)
	unsigned int nbSpikes;	///< the number of spikes the neuron has sent during its lifetime
	Time lastSpike;			///< the time of the last spike the Neuron sent
	Time currentTime;		///< the time it is currently in the Neuron
	std::array<Potential, 2*constants::D_IN_STEP> buffer;	///< a buffer that implements the transmission delay of spikes
	bool excitatory;		///< tells if a Neuron is excitatory (true) or inhibitory (false). this changes the amplitude of the spike
	
	static constexpr Time refractoryStep = (constants::REFRACTORY_TIME/constants::H);	///< the refractory time given in steps
	static constexpr double mbResistance = (constants::TAU/constants::C);				///< the electrical resistance of the membrane
	static constexpr double ODEFactor1 = (exp(-constants::H/constants::TAU));			///< the first constant used in the update of the potential 
	static constexpr double ODEFactor2 = (mbResistance*(1-ODEFactor1));					///< the second constant used in the update of the potential 

	/*!
	 * @brief utilitary method that tells if a Neuron is refractory.
	 * @brief a Neuron is refractory if it has spiked more recently than refractoryStep
	 * @param nothing
	 * @return true if the Neuron is refractory, false if not
	 */
	bool isRefractory();
	
	/*!
	 * @brief utilitary method that updates the membrane potential of the Neuron. Called in Neuron::update
	 * @param the external current and an amplitude that corresponds to the sum of the spikes in the buffer with the noise
	 * @return void
	 */
	void updatePotential(const double& extI, const Potential& J);
	
	/*!
	 * @brief utilitary method that returns the position in the buffer that corresponds to the given Time (used to implement delay in transmission of spikes)
	 * @param the Time we want the correspondance in buffer
	 * @return the position in the buffer that corresponds to the given Time
	 */
	unsigned int inBuffer(const Time&) const;
};

#endif // NEURON_H
