#include <iostream>
#include "../googletest/include/gtest/gtest.h"

#include "../src/Neuron.h"
#include "../src/Simulation.h"


TEST (singleNeuron, noSpike) {
	Neuron n;
	n.setMbPotential(0.0);
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
	n.setMbPotential(0.0);
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
	n.setMbPotential(0.0);
	bool spiked(false);
	
	spiked = n.update(1.01, 924, 0.0);
	EXPECT_EQ(n.getNbSpikes(), 0);
	EXPECT_FALSE(spiked);
	
	spiked = n.update(1.01, 925, 0.0);
	EXPECT_EQ(n.getNbSpikes(), 1);
	EXPECT_TRUE(spiked);
	EXPECT_EQ(n.getMbPotential(), constants::RESET_POTENTIAL);
	spiked = n.update(944);
	EXPECT_EQ(n.getMbPotential(), constants::RESET_POTENTIAL);
	EXPECT_FALSE(spiked);
	n.setMbPotential(0.0);
	
	spiked = n.update(1.01, 1868, 0.0);
	EXPECT_EQ(n.getNbSpikes(), 1);
	EXPECT_FALSE(spiked);
	
	spiked = n.update(1.01, 1869, 0.0);
	EXPECT_EQ(n.getNbSpikes(), 2);
	EXPECT_TRUE(spiked);
	EXPECT_EQ(n.getMbPotential(), constants::RESET_POTENTIAL);
}

TEST (twoNeurons, spikeDelay) {
	Neuron n1;
	n1.setMbPotential(0.0);
	Neuron n2;
	n2.setMbPotential(0.0);
	int j(0), k(0);
	bool spiked(false);
	for (int i(0);i<941;++i) {
		spiked = n1.update(1.01, i, 0.0);
		n2.update(0.0, i, 0.0);
		if (spiked) {
			j=i;
			n2.receiveSpike(constants::JE, i+constants::D_IN_STEP);
		}
		if (n2.getMbPotential()!=0.0) {
			k=i;
		}
	}
	EXPECT_EQ(j+constants::D_IN_STEP, k);
	EXPECT_EQ(n2.getMbPotential(), 0.1);
}

TEST (twoNeurons, triggerSpike) {
	Neuron n1;
	n1.setMbPotential(0.0);
	Neuron n2;
	n2.setMbPotential(0.0);
	bool spiked(false);
	for (int i(0);i<941;++i) {
		spiked = n1.update(1.01, i, 0.0);
		n2.update(1.005, i, 0.0);
		if (spiked) {
			n2.receiveSpike(constants::JE, i+constants::D_IN_STEP);
		}
	}
	EXPECT_EQ(n2.getNbSpikes(), 0);
	EXPECT_EQ(n2.getSpikeTime(), 0);
	spiked = n2.update(1.005, 942, 0.0);
	EXPECT_TRUE(spiked);
	EXPECT_EQ(n2.getMbPotential(), constants::RESET_POTENTIAL);
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
