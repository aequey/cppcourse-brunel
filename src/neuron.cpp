#include "neuron.h"
#include <iostream>

Neuron::Neuron()
	: mbPotential(0.0), spikes({}) {}

void Neuron::update(const double& dt) {}
