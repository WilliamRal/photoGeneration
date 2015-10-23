//
//	weightedRandMachine.cpp
//	Assignment1
//
//	Created by Binghong Fu on 9/23/15.
//	copyright ©2015 Binghong Fu. All rights reserved.
//

#ifndef weightedRandMachine_hpp
#define weightedRandMachine_hpp

#include <random>
#include <vector>

using namespace std;

namespace ga{
	class WeightedRandMachine{
		const vector<double> & prob;
		static default_random_engine randEngine;
	public:
		WeightedRandMachine(const vector<double> & probabilities) : prob(probabilities){}
		int nextInt();
	};
}

#endif /* weightedRandMachine_hpp */
