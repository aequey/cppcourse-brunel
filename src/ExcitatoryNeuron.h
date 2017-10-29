#ifndef EXCITATORY_NEUR_H
#define EXCITATORY_NEUR_H

#include "Neuron.h"
#include "Constants.h"


class ExcitatoryNeuron : public Neuron {
public:	
	
	virtual Potential getJ() const override final;	
	virtual void receiveSpike(const Neuron* neur, const Time& delay) override final;
	virtual Potential getJToExcitatory() const override final;
	
private:
	
};



#endif // EXCITATORY_NEUR_H
