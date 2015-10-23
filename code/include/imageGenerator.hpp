//
//  imageGenerator.hpp
//  Assignment1
//
//  Created by Binghong Fu on 9/22/15.
//  Copyright © 2015 Binghong Fu. All rights reserved.
//

#ifndef imageGenerator_hpp
#define imageGenerator_hpp

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <ctime>        
#include <chrono>
#include <vector>

#include "image.hpp"
#include "parameters.h"
#include "mutationFactory.hpp"
#include <sys/stat.h>
#include "weightedRandMachine.hpp"

using namespace cv;
using namespace std;

namespace ga {
    class ImageGenerator{
    
    private:
        string imagePath;
        default_random_engine * randomEngine;
        Mat * sourceImage;
        vector<Image * > imagePool;
        MutationFactory * mutationFactory;
        fstream logFile;
        
        int numOfParents;
        int numOfChildren;
        
        void generateChildren();
        void executeMutation();
        void eliminateImage();
        
        void createLogFile(string logPath, string sourcePath);
        
        static bool comparator(const Image * img1, const Image * img2);
        
    public:
        void generate(int numOfGeneration);
        Mat getFinalImage();
        
        ImageGenerator(string sourcePath,
                       string logPath,
                       int numOfParent,
                       int numOfChildren);
        ~ImageGenerator();
    };
}

#endif /* imageGenerator_hpp */
