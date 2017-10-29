#include "ExcitatoryNeuron.h"
#include "Constants.h"


Potential ExcitatoryNeuron::getJ() const {
	return constants::JE;
}

void ExcitatoryNeuron::receiveSpike(const Neuron* neur, const Time& delay) {
	Potential amplitude(neur->getJToExcitatory());
	Neuron::receiveSpike(amplitude, delay);
}

Potential ExcitatoryNeuron::getJToExcitatory() const {
	return getJ();
}
