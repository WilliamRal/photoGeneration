##Photograph learner
This program can learn a photo, and generate a polygon version of it (a photo made up of a lot of polygons). It starts with a random guess (pretty bad usually) and evolves using genetic algorithm.

##How to use:
1. Make the project by `make`
2. Run the program by `./run [N] [K] [E]`
3. To use other images, change original images in originalImages directory, and update imagePaths by adding the name.
4. Generated image files are in generatedImage directory.
5. Log files are in log directory.
6. After execution, use “make clean” to erase generated images and compiled file.

##Note:

You will need opencv library and GNU to run this program