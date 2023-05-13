#ifndef globals_h
#define globals_h

// This file should be included only in Parser.cpp

#include <iostream>
using namespace std;
#include <string>

#define NUM_KEYWORDS 6
string keyWordsList[NUM_KEYWORDS]={"shape", "group", "move", "delete", "draw", "pool"};

#define NUM_TYPES 3
string shapeTypesList[NUM_TYPES]={"ellipse", "rectangle","triangle"};

#endif /* globals_h */

