//
//  imageGenerator.cpp
//  Assignment1
//
//  Created by Binghong Fu on 9/22/15.
//  Copyright © 2015 Binghong Fu. All rights reserved.
//

#include "../include/imageGenerator.hpp"

ga::ImageGenerator::ImageGenerator(string sourcePath,
                                   string logPath,
                                   int numOfParent,
                                   int numOfChildren){
    
    this->imagePath = sourcePath.substr(0, sourcePath.size() - 4);
    this->numOfChildren = numOfChildren;
    this->numOfParents = numOfParent;
   	
    randomEngine = new default_random_engine(1);
    sourceImage = new Mat(imread(ORIGINAL_IMAGE_FOLDER_PATH + sourcePath));
    
    this->mutationFactory = new MutationFactory(randomEngine);
    
    for(int i = 0; i < numOfParents; ++i){
        imagePool.push_back(new Image(*randomEngine, *sourceImage));
    }
    
    createLogFile(logPath, sourcePath);
    
    cout << "Generate from original image : " + sourcePath << endl;
    cout << "Log file generated in : " << logPath << endl;
}

ga::ImageGenerator::~ImageGenerator(){
    delete randomEngine;
    delete sourceImage;
    delete mutationFactory;
    
    for(int i = 0; i < imagePool.size(); ++i){
        delete imagePool[i];
    }
    logFile.close();
    
}

void ga::ImageGenerator::createLogFile(string logPath, string sourcePath){
    
    chrono::time_point<chrono::system_clock> time;
    time = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(time);
    logFile.open(logPath.c_str(), fstream::app | fstream::in | fstream::out);
    logFile << endl << endl << endl;
	logFile << "Created Time : " << ctime(&currentTime) << endl;
    logFile << "Original Image : " << sourcePath << endl;
    logFile << "Parameters : " << endl << "\tN = " << numOfParents << endl
    << "\tK = " << numOfChildren << endl << "------------------------------------------------" << endl;
    
    logFile << "Mutation Parameters : " << endl;
    logFile << "\tCOLOR_DEVIATION = " << COLOR_DEVIATION << endl
            << "\tALPHA_DEVIATION = " << ALPHA_DEVIATION << endl
            << "\tVERTEX_DEVIATION = " << VERTEX_DEVIATION << endl
    << "\tVERTEX_LOCATION_DEVIATION = " << VERTEX_LOCATION_DEVIATION << endl
    << "\tNEW_POLYGON_VERTEX_DEVIATION = " << NEW_POLYGON_VERTEX_DEVIATION << endl << endl;
    
    logFile << "Mutation Probabilities : " << endl;
    logFile << "\tCOLOR_MUTATION_FACTOR = " << COLOR_MUTATION_FACTOR << endl;
    logFile << "\tVERTEX_ADDITION_FACTOR = " << VERTEX_ADDITION_FACTOR << endl;
    logFile << "\tVERTEX_DELETION_FACTOR = " << VERTEX_DELETION_FACTOR << endl;
    logFile << "\tVERTEX_MUTATION_FACTOR = " << VERTEX_MUTATION_FACTOR << endl;
    logFile << "\tALPHA_MUTATION_FACTOR = " << ALPHA_MUTATION_FACTOR << endl;
    logFile << "\tRANDOM_POLYGON_FACTOR = " << RANDOM_POLYGON_FACTOR << endl;
    logFile << "\tPOLYGON_SWAP_FACTOR = " << POLYGON_SWAP_FACTOR << endl;
    
    logFile << "------------------------------------------------" << endl << endl << endl;

}


void ga::ImageGenerator::generateChildren(){

	vector<double> scores;
    for(int i = 0; i < numOfParents; ++i)
		scores.push_back(imagePool[i]->im_score);
	WeightedRandMachine parentSelector(scores);
	
    uniform_int_distribution<int> crossover(0, NUM_OF_POLYGONS);
    
    for(int i = 0; i < numOfChildren; ++i){
      	int father = parentSelector.nextInt();
		int mother = parentSelector.nextInt();

        Image * child = new Image(*imagePool[father], *imagePool[mother], crossover(*randomEngine));
        imagePool.push_back(child);
    }
}

void ga::ImageGenerator::executeMutation(){
    for(int i = numOfParents; i < imagePool.size(); ++i){
        mutationFactory->mutateImage(imagePool[i]);
    }
}

void ga::ImageGenerator::eliminateImage(){
    std::sort(imagePool.begin(), imagePool.end(), ImageGenerator::comparator);
    for(int i = numOfParents; i < imagePool.size(); ++i){
        delete imagePool[i];
    }
    imagePool.resize(numOfParents);
}

void ga::ImageGenerator::generate(int numOfGeneration){
    
    //------------ log and cout ---------------//
    
    logFile << "Number of generations : " << numOfGeneration << endl;
    logFile << "Scores: "<< endl;
    
    cout << endl << "Image input successful ..." << endl;
    cout << "Begin generating ... " << endl;
    cout << "Highest scores : (Current generation / Total generation) " << endl;
    
    //-----------------------------------------//
    stringstream imageDirPath;
    imageDirPath << IMAGE_FOLDER_PATH << imagePath;
    
    mkdir(imageDirPath.str().c_str(), S_IRWXO | S_IRWXU | S_IRWXG);
    
    for(int i = 0; i < numOfGeneration; ++i){
        generateChildren();
        executeMutation();
        eliminateImage();
        
        if(i % (1000/numOfChildren) == 0){
            ostringstream outputPath;
            outputPath << IMAGE_FOLDER_PATH <<
                    imagePath << "/PolyImage_" << imagePool[0]->im_score <<".jpg";
            imwrite(outputPath.str(), imagePool[0]->getMat());
            logFile << imagePool[0]->im_score << ", ";
            logFile.flush();
            
            cout << i << "/" << numOfGeneration << "\t : " << imagePool[0]->im_score << endl;
        }
    }
    
    
    logFile << endl << "----------------------" << endl <<
            "Best Score is : " << imagePool[0]->im_score << endl;
    cout << endl << "-------------------" << endl << "Best Score is : " << imagePool[0]->im_score << endl;
    cout << "Generation finished. " << endl << endl;
}

Mat ga::ImageGenerator::getFinalImage(){
    return imagePool[0]->getMat();
}



bool ga::ImageGenerator::comparator(const Image * img1 , const Image * img2){
    return img1->im_score > img2->im_score;
}



