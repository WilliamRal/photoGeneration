all: include/draw.hpp include/imageGenerator.hpp include/image.hpp include/mutationFactory.hpp include/parameters.h include/weightedRandMachine.hpp
	g++ -std=c++11 `pkg-config --cflags opencv` `pkg-config --libs opencv` -o run src/draw.cpp src/image.cpp src/imageGenerator.cpp src/main.cpp src/mutationFactory.cpp src/weightedRandMachine.cpp

clean: 
	rm run
	rm -r generatedImages
