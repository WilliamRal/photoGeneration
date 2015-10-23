//
//  mutationFactory.hpp
//  Assignment1
//
//  Created by Binghong Fu on 9/22/15.
//  Copyright © 2015 Binghong Fu. All rights reserved.
//

#ifndef mutationFactory_hpp
#define mutationFactory_hpp

#include "image.hpp"
#include <random>
#include <vector>
#include "weightedRandMachine.hpp"

/***************************************
 *          Mutation Factory           *
 *    Provide all kinds of mutations   *
 
 Note:
 The randomEngine should keep valid when
 using the class.

 Sample:
 
    default_random_engine * e =
        new default_random_engine;
    Image * img = new Image(parameter);
    
    MutationFactory mf(e);
    mf.mutateImg(img);
    delete e;
 
****************************************/




namespace ga {
    class MutationFactory{
    private:
        default_random_engine * randomEngine;
        WeightedRandMachine * dice;

        void addRandomVertex(Image * img, int polygonIndex);
        void deleteRandomVertex(Image * img, int polygonIndex);
        void addRandomPolygon(Image * img, int polygonIndex);
        void swapPolygons(Image * img, int polygonIndex1, int polygonIndex2);
        void vertexLocationMutation(Image * img, int polygonIndex);
        void colorMutation(Image * img, int polygonIndex);
        void alphaMutation(Image * img, int polygonIndex);
        
        double boundDouble(double num, double upperBound, double lowerBound);
        //int dice(vector<double> probabilities);
        
    public:
        MutationFactory(default_random_engine * randomEngine);
        
        void mutateImage(Image * img);
    };
}

#endif /* mutationFactory_hpp */
