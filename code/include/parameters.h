//
//  parameters.h
//  Assignment1
//
//  Created by Binghong Fu on 9/22/15.
//  Copyright © 2015 Binghong Fu. All rights reserved.
//

#ifndef parameters_h
#define parameters_h

const int MAX_VERTICES = 8;
const int MIN_VERTICES = 3;
const int NUM_OF_POLYGONS = 100;

const std::string imgName_1 = "mona_lisa";
const std::string imgName_2 = "charles_darwin";
const std::string imgName_3 = "claude_monet";
const std::string imgName_4 = "lenna";
const std::string imgName_5 = "sun_flowers";

const std::string LOG_FOLDER_PATH = "log/";
const std::string IMAGE_FOLDER_PATH = "generatedImages/";
const std::string ORIGINAL_IMAGE_FOLDER_PATH = "originalImages/";


/*------------------ Mutation Parameters ----------------*/
const double COLOR_DEVIATION = 0.1;
const double ALPHA_DEVIATION = 0.1;
const double VERTEX_DEVIATION = 0.1;
const double VERTEX_LOCATION_DEVIATION = 0.01;

const double NEW_POLYGON_VERTEX_DEVIATION = 0.25;


const int COLOR_MUTATION_FACTOR = 3;
const int VERTEX_ADDITION_FACTOR = 1;
const int VERTEX_DELETION_FACTOR = 1;
const int VERTEX_MUTATION_FACTOR = 1;
const int ALPHA_MUTATION_FACTOR = 2;
const int RANDOM_POLYGON_FACTOR = 2;
const int POLYGON_SWAP_FACTOR = 2;



#endif /* parameters_h */
