#include <iostream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <string>

#include "Cache.h"
#include "CacheEntry.h"
#include "CacheSet.h"

#define PATH "C:\\Users\\crisc\\CLionProjects\\CacheSimulator\\addresses.dat"
#define NUM_ARGS 7

using namespace std;

map<string, int>* verifyArgs(int argc, char** argv);

int main(int argc, char** argv)
{


    map<string, int>* args = verifyArgs(argc, argv);
    if(args == nullptr)
    {
        cerr << "Improper command line arguments!";
        return 1;
    }




    return 0;
}

// Verify arguments are valid and return pointer to a map if they are
map<string, int>* verifyArgs(int argc, char** argv)
{
    if(argc != NUM_ARGS)
    {
        return nullptr;
    }
    vector<string> options;
    vector<int> values;

    // make sure options are valid
    for(size_t i = 1;i <= NUM_ARGS; i+=2)
    {
        if(argv[i] != "-s" && argv[i] != "-c" && argv[i] != "-b")
        {
            return nullptr;
        }
        options.push_back(argv[i]);
    }
    // make sure numbers are valid
    for(size_t i = 2;i <= NUM_ARGS; i+=2)
    {
        char* temp;
        int num = strtol(argv[i], &temp, 0);
        if (temp == argv[i] || *temp)
        {
            return nullptr;
        }
        // TODO: verify args are powers of 2
        values.push_back(num);
    }

    map<string, int>* args = new map<string, int>;
    for(size_t i = 0;i<values.size();i++)
    {
        args->at(options[i]) = values[i];
    }
    return args;
}