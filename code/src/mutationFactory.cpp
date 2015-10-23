//
//  mutationFactory.cpp
//  Assignment1
//
//  Created by Binghong Fu on 9/22/15.
//  Copyright © 2015 Binghong Fu. All rights reserved.
//

#include "../include/mutationFactory.hpp"

ga::MutationFactory::MutationFactory(default_random_engine * randomEngine){
    this->randomEngine = randomEngine;
}

void ga::MutationFactory::mutateImage(Image * img){
    uniform_int_distribution<int> polygonSelector(0, NUM_OF_POLYGONS-1);
    int polygonIndex = polygonSelector(*randomEngine);

    vector<double> factors;
    factors.push_back(COLOR_MUTATION_FACTOR);
    factors.push_back(VERTEX_ADDITION_FACTOR);
    factors.push_back(VERTEX_DELETION_FACTOR);
    factors.push_back(VERTEX_MUTATION_FACTOR);
    factors.push_back(ALPHA_MUTATION_FACTOR);
    factors.push_back(RANDOM_POLYGON_FACTOR);
    factors.push_back(POLYGON_SWAP_FACTOR);
  
	dice = new WeightedRandMachine(factors);

    int choice = dice->nextInt();
    switch (choice) {
        case 0:
            colorMutation(img, polygonIndex);
            break;
        case 1:
            addRandomVertex(img, polygonIndex);
            break;
        case 2:
            deleteRandomVertex(img, polygonIndex);
            break;
        case 3:
            vertexLocationMutation(img, polygonIndex);
            break;
        case 4:
            alphaMutation(img, polygonIndex);
            break;
        case 5:
            addRandomPolygon(img, polygonIndex);
            break;
        case 6:
            uniform_int_distribution<int> secondIndexSelector(0, NUM_OF_POLYGONS-1);
            int secondIndex = secondIndexSelector(*randomEngine);
            swapPolygons(img, polygonIndex, secondIndex);
            break;
    }
    
    img->updateScore();
}

void ga::MutationFactory::colorMutation(Image * img, int polygonIndex){
    
    Scalar originalColor = img->colors[polygonIndex];
    normal_distribution<double> redDistribution(originalColor.val[0], 256 * COLOR_DEVIATION);
    normal_distribution<double> greenDistribution(originalColor.val[1], 256 * COLOR_DEVIATION);
    normal_distribution<double> blueDistribution(originalColor.val[2], 256 * COLOR_DEVIATION);
    
    img->colors[polygonIndex].val[0] = max(min((int)redDistribution(*randomEngine), 255), 0);
    img->colors[polygonIndex].val[1] = max(min((int)greenDistribution(*randomEngine), 255), 0);
    img->colors[polygonIndex].val[2] = max(min((int)blueDistribution(*randomEngine), 255), 0);
}

void ga::MutationFactory::addRandomPolygon(Image * img, int polygonIndex){
    
    uniform_int_distribution<int> xValGen(0, img->imageWidth-1);
    uniform_int_distribution<int> yValGen(0, img->imageHeight-1);
    uniform_int_distribution<int> colorValGen(0, 255);
    uniform_real_distribution<double> alphaValGen(0, 1);
    
    int centerX = xValGen(*randomEngine);
    int centerY = yValGen(*randomEngine);
    
    normal_distribution<double> normXValGen(centerX, NEW_POLYGON_VERTEX_DEVIATION * img->imageWidth);
    normal_distribution<double> normYValGen(centerY, NEW_POLYGON_VERTEX_DEVIATION * img->imageHeight);
    
    for(int i = 0; i < 3; ++i){
        img->polyArr[polygonIndex][i].x = max(min((int)normXValGen(*randomEngine), 255), 0);
        img->polyArr[polygonIndex][i].y = max(min((int)normYValGen(*randomEngine), 255), 0);
    }
    
    img->vertexCounts[polygonIndex] = 3;
    img->colors[polygonIndex].val[0] = colorValGen(*randomEngine);
    img->colors[polygonIndex].val[1] = colorValGen(*randomEngine);
    img->colors[polygonIndex].val[2] = colorValGen(*randomEngine);
    img->colors[polygonIndex].val[3] = alphaValGen(*randomEngine);
}

void ga::MutationFactory::deleteRandomVertex(Image * img, int polygonIndex){
    if(img->vertexCounts[polygonIndex] == MIN_VERTICES) return;
    uniform_int_distribution<int> vertexSelector(0, img->vertexCounts[polygonIndex] - 1);
    int vertexIndex = vertexSelector(*randomEngine);
    
    img->polyArr[polygonIndex][vertexIndex] = img->polyArr[polygonIndex][img->vertexCounts[polygonIndex] - 1];
    img->vertexCounts[polygonIndex]--;
}

void ga::MutationFactory::addRandomVertex(Image * img, int polygonIndex){
    if(img->vertexCounts[polygonIndex] == MAX_VERTICES) return;
    uniform_int_distribution<int> verticesSelector(0, img->vertexCounts[polygonIndex] - 1);
    int vertex1 = verticesSelector(*randomEngine);
    int vertex2 = verticesSelector(*randomEngine);
    
    double midX =  (double)img->polyArr[polygonIndex][vertex1].x / 2 +
                    (double)img->polyArr[polygonIndex][vertex2].x / 2;
    
    double midY =  (double)img->polyArr[polygonIndex][vertex1].y / 2 +
                    (double)img->polyArr[polygonIndex][vertex2].y / 2;
        
    normal_distribution<double> xValGen(midX, img->imageWidth * VERTEX_LOCATION_DEVIATION);
    normal_distribution<double> yValGen(midY, img->imageHeight* VERTEX_LOCATION_DEVIATION);
        
    img->polyArr[polygonIndex][img->vertexCounts[polygonIndex]].x =
            max(min((int)xValGen(*randomEngine), img->imageWidth), 0);
    img->polyArr[polygonIndex][img->vertexCounts[polygonIndex]].y =
            max(min((int)yValGen(*randomEngine), img->imageHeight), 0);
    img->vertexCounts[polygonIndex]++;

}

void ga::MutationFactory::swapPolygons(Image * img, int polygonIndex1, int polygonIndex2){
    for(int i = 0; i < MAX_VERTICES; ++i){
        Point temp(img->polyArr[polygonIndex1][i].x, img->polyArr[polygonIndex1][i].y);
        img->polyArr[polygonIndex1][i] = img->polyArr[polygonIndex2][i];
        img->polyArr[polygonIndex2][i] = temp;
    }
    
    Scalar temp = img->colors[polygonIndex1];
    img->colors[polygonIndex1] = img->colors[polygonIndex2];
    img->colors[polygonIndex2] = temp;
    
    int vertices = img->vertexCounts[polygonIndex1];
    img->vertexCounts[polygonIndex1] = img->vertexCounts[polygonIndex2];
    img->vertexCounts[polygonIndex2] = vertices;
}

void ga::MutationFactory::alphaMutation(Image * img, int polygonIndex){
    double originalAlpha = img->colors[polygonIndex].val[3];
    normal_distribution<double> alphaGenerator(originalAlpha, ALPHA_DEVIATION);
    img->colors[polygonIndex].val[3] = boundDouble(alphaGenerator(*randomEngine), 1, 0);
}

void ga::MutationFactory::vertexLocationMutation(Image * img, int polygonIndex){
    uniform_int_distribution<int> vertexSelector(0, img->vertexCounts[polygonIndex] - 1);
    int vertex = vertexSelector(*randomEngine);
    
    normal_distribution<double> xValGen(img->polyArr[polygonIndex][vertex].x,
                                        img->imageWidth * VERTEX_DEVIATION);
    normal_distribution<double> yValGen(img->polyArr[polygonIndex][vertex].y,
                                        img->imageHeight * VERTEX_DEVIATION);
    
    img->polyArr[polygonIndex][vertex].x = max(min((int) xValGen(*randomEngine), img->imageWidth), 0);
    img->polyArr[polygonIndex][vertex].y = max(min((int) yValGen(*randomEngine), img->imageHeight), 0);

}

double ga::MutationFactory::boundDouble(double num, double upperBound, double lowerBound){
    if(num > upperBound)    return upperBound;
    if(num < lowerBound)    return lowerBound;
    return num;
}

/*
int ga::MutationFactory::dice(vector<double> probabilities){
    int index = 0;
    
    double totalProb = 0;
    for(size_t i = 0; i < probabilities.size(); ++i){
        totalProb += probabilities[i];
    }
    uniform_real_distribution<double> diceThrower(0, totalProb);
    double diceVal = diceThrower(*randomEngine);
    while(diceVal > probabilities[index]){
        diceVal -= probabilities[index];
        index++;
    }
    return index;
}
*/
