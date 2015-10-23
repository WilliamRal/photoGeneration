//
//  image.cpp
//  Assignment1
//
//  Created by Binghong Fu on 9/22/15.
//  Copyright © 2015 Binghong Fu. All rights reserved.
//

#include "../include/image.hpp"

ga::Image::Image(default_random_engine & randEngine, Mat & source){
    imageWidth = source.cols;
    imageHeight = source.rows;
    
    this->source = &source;
    
    uniform_int_distribution<int> xValGen(0, imageWidth-1);
    uniform_int_distribution<int> yValGen(0, imageHeight-1);
    uniform_int_distribution<int> BGRgen(0,255);
    uniform_real_distribution<double> alphaGen(0,1);
    
    for (int i = 0; i < NUM_OF_POLYGONS; i++) {
        vertexCounts[i] = MIN_VERTICES;
        
        for (int j = 0; j < vertexCounts[i]; j++) {
            polyArr[i][j].x = xValGen(randEngine);
            polyArr[i][j].y = yValGen(randEngine);
        }
        
        colors[i] = Scalar(BGRgen(randEngine), BGRgen(randEngine),
                           BGRgen(randEngine), alphaGen(randEngine));
        polygons[i] = &polyArr[i][0];
    }
    
    updateScore();

}

ga::Image::Image(const Image & img1, const Image & img2, const int crossOver){
    imageWidth = img1.imageWidth;
    imageHeight = img1.imageHeight;
    
    this->source = img1.source;
    
    const Image * copyImg = &img1;
    
    for(int i = 0; i < NUM_OF_POLYGONS; ++i){
        if(i == crossOver)  copyImg = &img2;
        
        vertexCounts[i] = copyImg->vertexCounts[i];
        colors[i] = copyImg->colors[i];
        for(int j = 0; j < vertexCounts[i]; ++j){
            polyArr[i][j] = copyImg->polyArr[i][j];
        }
        polygons[i] = &polyArr[i][0];
    }
    
    updateScore();
}

double ga::Image::updateScore(){
    im_score = score(renderPolyImage(imageHeight,
                                            imageWidth,
                                            NUM_OF_POLYGONS,
                                            polygons,
                                            vertexCounts,
                                            colors), *source);
    return im_score;
}

Mat ga::Image::getMat(){
    return renderPolyImage(imageHeight,
                    imageWidth,
                    NUM_OF_POLYGONS,
                    polygons,
                    vertexCounts,
                    colors);
}
