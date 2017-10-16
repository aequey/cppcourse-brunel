#include <iostream>
#include "../src/neuron.h"
#include "../src/simulation.h"
#include "../googletest/include/gtest/gtest.h"

TEST (potentialTest, oneUpdate) {
	Neuron n;
	n.update(1.0, 0);
	EXPECT_EQ(n.getMbPotential(), 0.0);
	n.update(1.0, 1); // update n with an Iext of 1.0 mV for 1 sim step
	EXPECT_NEAR(20.0*(1.0-std::exp(-0.1/20.0)), n.getMbPotential(), 0.000000001);
}

TEST (potentialTest, neverSpike) {
	Neuron n;
	bool spiked;
	spiked = n.update(1.0, 10000000);
	EXPECT_EQ(spiked, false);
	EXPECT_LT(n.getMbPotential(), 20.0);
}

TEST (potentialTest, spikeTimes) {
	Neuron n;
	bool spiked;
	spiked = n.update(1.01, 924);
	EXPECT_EQ(spiked, false);
	spiked = n.update(1.01, 925);
	EXPECT_EQ(spiked, true);
	spiked = n.update(1.01, 1868);
	EXPECT_EQ(spiked, false);
	spiked = n.update(1.01, 1869);
	EXPECT_EQ(spiked, true);
	spiked = n.update(1.01, 2812);
	EXPECT_EQ(spiked, false);
	spiked = n.update(1.01, 2813);
	EXPECT_EQ(spiked, true);

	
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
