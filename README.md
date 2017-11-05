# Neuron_project

# Purpose of the program and model discussion
We want to simulate 12500 Neurons using the model of Brunel that has been published in 2000.
General idea of the model : 

•	A neuron has a membrane potential. If it gets an external current or stimulation, this potential will change.

•	If the potential reaches reaches a certain threshold, the Neuron will spike (i.e. send a signal to other neurons).

•	After the spike, the potential is reset and the processus can restart.

•	They are two types of neurons : excitatory send positive signals (that tend to bring the potential of the neurons that are receiving the spike closer to the threshold), and inhibitory send negative signals.

•	Since we only simulate 12500 neurons (less than a mm^3 of brain), we implement randomly generated external spikes.

# Simulation
In our simulations, we play with two parameters : G, the ratio of strength of connexions between the inhibitory neurons and the excitatory ones (a ratio of 2 means that output connexions of inhibitory neurons are twice as strong as output connexions of excitatory neurons) and ETA, something that relates to the rate of external spikes.
A balanced network is when G and ETA are compensating each other.

Our goal is to reproduce four results of the paper (we save the spiking times of each neuron) :

A) G=3    ETA=2
B) G=6	  ETA=4
C) G=5	  ETA=2
D) G=4.5	ETA=0.9

A normal simulation runs for a simulation time of 1000 ms.

Here is an indicative time that takes a simulation of 1000 ms for each of the Brunel parameters with EPFL computers :

A) ~55 s

B) ~30 s

C) ~20 s

D) ~10 s

The time of the simulation strongly depends on the number of spikes sent in each ster of simultion.

# How to use the program
To run the simulation, first compile the program : go on build directory and type :

cmake ..

make

You can execute the simulation by typing ./main (or run the tests with ./neuronTest) in the same directory.

By default, G=5 and ETA=2. If you want to change these parameters, go to the file src/Constants.h. The two parameters to modify are the first of the list. You'll have to recompile the program.

If you want to change the simulation time, go to src/main.cpp and change the parameter of the constructor of Simulation that corresponds to the time. If you want to change the name of the file of results, do it the same way.

res/Graph.ipynb allows you to have graphs of  the results using for example jupyter notebook.

The code is commented to be compatible with Doxygen. To see it go to build and type : 

make doc

Before doing this, ensure you have typed cmake ..
You'll find the documentaton on dox/html/index.html
