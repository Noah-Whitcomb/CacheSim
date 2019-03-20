// John Gaboriault-Whitcomb

#include <iostream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <fstream>

#include "Cache.h"
#include "CacheEntry.h"
#include "CacheSet.h"
#include "Util.h"

#define INPUT_PATH R"(C:\Users\crisc\CLionProjects\CacheSimulator\CacheSim\addresses_allsame.dat)"
#define OUTPUT_PATH R"(C:\Users\crisc\CLionProjects\CacheSimulator\CacheSim\debug_log.txt)"

using namespace std;

bool debug = false;
ofstream outputfile;

int main(int argc, char** argv)
{
    if(debug)
    {
        outputfile.open(OUTPUT_PATH);
        if(!outputfile)
        {
            cout << "Could not open output file" << endl;
            return 1;
        }
    }
    map<string, int>* args = verify_args(argc, argv);
    if(args == nullptr)
    {
        cout << "Improper command line arguments!";
        return 1;
    }

    Cache cache = Cache(args->at("-s"), args->at("-a"), args->at("-b"));

    ifstream file;
    file.open(INPUT_PATH);
    if(!file)
    {
        cout << "Failed to open file!";
        return 1;
    }
    string read_or_write;
    int address;
    while(file >> read_or_write >> address)
    {
        if(debug)
        {
            cout << read_or_write << " " << address << endl;
            outputfile << read_or_write << " " << address << endl;
        }
        if(read_or_write == "r")
        {
            cache.readByte(address);
        }
        if(read_or_write == "w")
        {
            // TODO: change this for higher levels
        }
    }

    //print summary
    cout << "cache size: " << args->at("-s") << endl;
    cout << "block size: " << args->at("-b") << endl;
    cout << "associativity: " << args->at("-a") << endl;
    cout << "total loads: " << cache.getMemoryReadCount() << endl;
    cout << "total writes: " << cache.getMemoryWriteCount() << endl;
    cout << "cache hits: " << cache.getHitCount() << endl;
    cout << "cache misses " << cache.getMissCount() << endl;
    cout << "miss rate: " << double(cache.getMissCount())/double(cache.getHitCount()) << " (misses per hit) " << endl;

    delete args;
    return 0;
}

