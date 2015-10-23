//
//  main.cpp
//  Assignment1 for EECS 492
//
//  Created by Binghong Fu on 9/22/15.
//  Copyright © 2015 Binghong Fu. All rights reserved.
//

#include "../include/imageGenerator.hpp"
#include <fstream>

using namespace cv;
using namespace std;
using namespace ga;

int main(int argc, const char * argv[]) {
    if(argc < 4){
        cerr << "Usage : " << "-bash-4.2$. /generateImage [N] [K] [E]" << endl;
        return -1;
    }
    
    
    
    const int N = atoi(argv[1]);
    const int K = atoi(argv[2]);
    const int E = atoi(argv[3]);
    
   // int N = 1, K = 1, E = 20000;
    int effort = (E - N) / K;
    
    mkdir(IMAGE_FOLDER_PATH.c_str(), S_IRWXU | S_IRWXG);
    string imagePath;
    fstream imagePathFinder("imagePaths");
    
    while(getline(imagePathFinder, imagePath)){
        stringstream logPath;
        logPath<< LOG_FOLDER_PATH<< imagePath.substr(0, imagePath.size() - 4) << ".log";
        
        ga::ImageGenerator generator(imagePath,logPath.str(), N, K);
        generator.generate(effort);
    }
    return 0;
}
