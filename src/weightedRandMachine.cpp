//
//  weightedRandMachine.cpp
//  Assignment1
//
//  Created by Binghong Fu on 9/23/15.
//  copyright ©2015 Binghong Fu. All rights reserved.
//

#include "../include/weightedRandMachine.hpp"

default_random_engine ga::WeightedRandMachine::randEngine = default_random_engine(1);

int ga::WeightedRandMachine::nextInt(){
	int index = 0;

	double totalProb = 0;
	for(size_t i = 0; i < prob.size(); ++i){
		totalProb += prob[i];
	}

	uniform_real_distribution<double> dice(0, totalProb);
	double val = dice(randEngine);
	while(val > prob[index]){
		val -= prob[index];
		index++;
	}

	return index;
}
