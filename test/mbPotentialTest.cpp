#include <iostream>
#include "../src/Neuron.h"
#include "../src/Simulation.h"
#include "../googletest/include/gtest/gtest.h"

TEST (singleNeuron, noSpike) {
	Neuron n;
	bool spiked;
	spiked = n.update(1.0, 0, 0.0);
	EXPECT_EQ(n.getNbSpikes(), 0);
	EXPECT_FALSE(spiked);
	EXPECT_EQ(n.getMbPotential(), 0.0);
	
	spiked = n.update(1.0, 1, 0.0); // update n with an Iext of 1.0 mV for 1 sim step
	EXPECT_EQ(n.getNbSpikes(), 0);
	EXPECT_FALSE(spiked);
	EXPECT_NEAR(20.0*(1.0-std::exp(-0.1/20.0)), n.getMbPotential(), 0.000000001);
	
	spiked = n.update(1.0, 10000, 0.0);
	EXPECT_EQ(n.getNbSpikes(), 0);
	EXPECT_FALSE(spiked);
	EXPECT_LT(n.getMbPotential(), 20);
	
	spiked = n.update(0.0, 20000, 0.0);
	EXPECT_EQ(n.getNbSpikes(), 0);
	EXPECT_FALSE(spiked);
	EXPECT_NEAR(n.getMbPotential(), 0, 0.000000001);	
}

TEST (singleNeuron, noSpikeNegative) {
	Neuron n;
	bool spiked;
	spiked = n.update(-1.0, 0, 0.0);
	EXPECT_FALSE(spiked);
	EXPECT_EQ(n.getMbPotential(), 0.0);
	
	spiked = n.update(-1.0, 1, 0.0); // update n with an Iext of -1.0 mV for 1 sim step
	EXPECT_EQ(n.getNbSpikes(), 0);
	EXPECT_FALSE(spiked);
	EXPECT_NEAR(-20.0*(1.0-std::exp(-0.1/20.0)), n.getMbPotential(), 0.000000001);
	
	spiked = n.update(-1.0, 10000, 0.0);
	EXPECT_EQ(n.getNbSpikes(), 0);
	EXPECT_FALSE(spiked);	
	EXPECT_GT(n.getMbPotential(), -20);
	
	spiked = n.update(0.0, 20000, 0.0);
	EXPECT_EQ(n.getNbSpikes(), 0);
	EXPECT_FALSE(spiked);	
	EXPECT_NEAR(n.getMbPotential(), 0, 0.000000001);	
}

TEST (singleNeuron, spikeTimes) {
	Neuron n;
	bool spiked(false);
	
	spiked = n.update(1.01, 924, 0.0);
	EXPECT_EQ(n.getNbSpikes(), 0);
	EXPECT_FALSE(spiked);
	
	spiked = n.update(1.01, 925, 0.0);
	EXPECT_EQ(n.getNbSpikes(), 1);
	EXPECT_TRUE(true);
	EXPECT_EQ(n.getMbPotential(), 0.0);
	
	spiked = n.update(1.01, 1868, 0.0);
	EXPECT_EQ(n.getNbSpikes(), 1);
	EXPECT_FALSE(false);
	
	spiked = n.update(1.01, 1869, 0.0);
	EXPECT_EQ(n.getNbSpikes(), 2);
	EXPECT_TRUE(true);
	EXPECT_EQ(n.getMbPotential(), 0.0);
	
	spiked = n.update(1.01, 2812, 0.0);
	EXPECT_EQ(n.getNbSpikes(), 2);
	EXPECT_FALSE(false);
	
	spiked = n.update(1.01, 2813, 0.0);
	EXPECT_EQ(n.getNbSpikes(), 3);
	EXPECT_TRUE(true);
	EXPECT_EQ(n.getMbPotential(), 0.0);
}

TEST (twoNeurons, spikeDelay) {
	Neuron n1;
	Neuron n2;
	int j(0), k(0);
	bool spiked(false);
	for (int i(0);i<941;++i) {
		spiked = n1.update(1.01, i, 0.0);
		n2.update(0.0, i, 0.0);
		if (spiked) {
			j=i;
			n2.receiveSpike(constants::JE, i+constants::D_IN_STEP-1); //LOL
		}
		if (n2.getMbPotential()!=0.0) {
			k=i;
		}
	}

	
	//~ while (currentTime_ <= simulationTime_) {
		
		//~ spike = n1.update(currentImput, currentTime_+1, 0.0);
		
		//~ if (spike) {
			//~ n2.receiveSpike(n1.getJ(), constants::D_IN_STEP);
		//~ }
		//~ n2.update(0.0, currentTime_+1, 0.0);
		

	//~ }
	


	EXPECT_EQ(j+constants::D_IN_STEP, k);
	EXPECT_EQ(n2.getMbPotential(), 0.1);
}



int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
