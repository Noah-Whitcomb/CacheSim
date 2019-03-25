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

#define INPUT_FILE "addresses.dat"
#define OUTPUT_FILE "debug_log.txt"

using namespace std;

bool debug = false;
bool write_to_file = false;
ofstream outputfile;

int main(int argc, char** argv)
{
    if(write_to_file)
    {
        outputfile.open(OUTPUT_FILE);
        if(!outputfile)
        {
            cout << "Could not open write_to_file file" << endl;
            return 1;
        }
    }

    map<string, int>* args = verify_args(argc, argv);
    if(args == nullptr)
    {
        cout << "Improper command line arguments!";
        return 1;
    }

    int numlines = args->at("-a")*args->at("-b");
    int numsets = args->at("-s")/numlines;

    Cache cache = Cache(numsets, args->at("-a"), args->at("-b"));

    ifstream file;
    file.open(INPUT_FILE);
    if(!file)
    {
        cout << "Failed to open file!";
        return 1;
    }
    string read_or_write;
    int address;
    while(file >> read_or_write >> address)
    {

        if(read_or_write == "r")
        {
            if(debug) cout << read_or_write << " " << address << endl;
            if(write_to_file) outputfile << read_or_write << " " << address << endl;
            cache.readByte(address);
        }
        if(read_or_write == "w")
        {
            // TODO: change this for higher levels
        }
    }
    //print summary
    cout << "cache size: " << args->at("-s") <<  endl;
    cout << "block size: " << args->at("-b") << endl;
    cout << "associativity: " << args->at("-a") << endl;
    cout << "total loads: " << cache.getMemoryReadCount() << endl;
    cout << "total writes: " << cache.getMemoryWriteCount() << endl;
    cout << "cache hits: " << cache.getHitCount() << endl;
    cout << "cache misses " << cache.getMissCount() << endl;
    cout << "miss rate: " << double(cache.getMissCount())/double(cache.getMemoryReadCount()) << endl;

    delete args;
    return 0;
}

