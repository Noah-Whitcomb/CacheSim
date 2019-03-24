// John Gaboriault-Whitcomb
#ifndef CACHESIMULATOR_UTIL_H
#define CACHESIMULATOR_UTIL_H

#include <map>
#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

//added boolean flag to easily control when things are printed
//static bool debug = true;
//static ofstream outputfile;

map<string, int>* verify_args(int argc, char **argv);
void writeToDebugFile(ofstream &output, int number);
void writeToDebugFile(ofstream &output, string str);

#endif //CACHESIMULATOR_UTIL_H
