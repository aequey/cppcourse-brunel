#include "InhibitoryNeuron.h"
#include "Constants.h"


Potential InhibitoryNeuron::getJ() const {
	return constants::JI;
}

//~ void Neuron::receiveSpike(const Neuron* neur, const Time& delay) {
	
//~ }

Potential InhibitoryNeuron::getJToExcitatory() const {
	return 0.0;
}
