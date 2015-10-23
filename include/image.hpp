//
//  image.hpp
//  Assignment1
//
//  Created by Binghong Fu on 9/22/15.
//  Copyright © 2015 Binghong Fu. All rights reserved.
//

#ifndef image_hpp
#define image_hpp

#include <opencv2/core/core.hpp>
#include <random>

#include "draw.hpp"
#include "parameters.h"

using namespace cv;
using namespace std;

namespace ga {      // Stands for genetic algorithm
    
    class Image{
    public:
        int imageHeight;
        int imageWidth;
        
        double im_score;
        
        Mat * source;
        
        const Point * polygons[NUM_OF_POLYGONS];
        int vertexCounts[NUM_OF_POLYGONS];
        Point polyArr[NUM_OF_POLYGONS][MAX_VERTICES];
        Scalar colors[NUM_OF_POLYGONS];
        
        //------------------------ Constructors ------------------------//
        //  Constructors in default updates score after constructed     //
        Image(default_random_engine & randEngine, Mat & source);
        Image(const Image & img1, const Image & img2, const int crossOver);
        Mat getMat();
        double updateScore();
    };
    
    
}
#endif /* image_hpp */
