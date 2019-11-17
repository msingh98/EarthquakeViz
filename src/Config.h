#ifndef config_h
#define config_h

#include <string>


// This variable isn't used outside this file, but makes specifying the other
// paths simpler.

// WINDOWS Path:
//const std:string DATA_DIR = "C:\\Users\\bjackson\\Documents\\classes\\comp494-graphics\\assignments\\asgn3-Earthquake\\data\\";

// MAC path
const std::string DATA_DIR = "/Users/ypang/Desktop/COMP465/code/earthquakeVis/data/";

// The file to load for the earth texture.
const std::string TEXTURE_PATH = DATA_DIR + "earth-2k.jpg";

// The earthquake database file
const std::string DATA_PATH = DATA_DIR + "earthquakes.txt";


#endif
