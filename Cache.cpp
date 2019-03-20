// John Gaboriault-Whitcomb
#include "Cache.h"
#include "Util.h"
using namespace std;


//	constructor
Cache::Cache(int setCount, int associativity, int lineSize)
{
    for (int i=0; i<setCount; i++)
    {
        cacheSets.emplace_back(CacheSet(lineSize, associativity));
    }

    number_of_sets = setCount;
    associativity_factor = associativity;
    line_size = lineSize;

    bits_in_set = power_of_two(setCount);	// computed, assumes the set count
    //	is a power of 2
    bits_in_offset = power_of_two(lineSize);	// computed, assumes lineSize
    //	is a power of 2
}



int  Cache::power_of_two(int value)
{
    int result = 0;
    const int limit  = 100;

    while (value > 1 && result < limit)
    {
        value = value >> 1;
        result ++;
    }
    if (value == 1)
        return result;
    else
        return -result;
}



void Cache::splitAddress( int address,
                          int &tag, int &setNumber, int &offset)
{
    int offset_mask,
            set_mask;

    offset_mask = (1 << bits_in_offset) - 1;
    offset = address & offset_mask;

    address = address >> bits_in_offset;
    set_mask = (1 << bits_in_set) - 1;
    setNumber = address & set_mask;

    tag = address >> bits_in_set;
}



bool Cache::readByte(int address)
{
// needs work!!

    int tag, setNumber, offset;

    splitAddress (address, tag, setNumber, offset);

    if(debug)
    {
        cout << "set number: " << setNumber << endl;
        outputfile << "set number: " << setNumber << " ";
        outputfile << "tag: " << tag << endl;
    }

    cacheSets[setNumber].incMemoryReadCount();

    int garbage;
    if (cacheSets[setNumber].hit(tag, garbage))
    {
        if(debug)
        {
            cout << "DEBUG: have a HIT" << endl;
            outputfile << "HIT" << endl;
        }
        cacheSets[setNumber].incHitCount();
    }
    else
    {
        if(debug)
        {
            cout << "DEBUG: have a MISS" << endl;
            outputfile << "MISS" << endl;
        }
        cacheSets[setNumber].incMissCount();
        cacheSets[setNumber].readByte(tag, offset);
    }
    if(debug) outputfile << "#################" << endl;
    return true;
}



int Cache::getHitCount()
{
    int hitCount = 0;
    for(size_t i = 0;i<cacheSets.size();i++)
    {
        hitCount += cacheSets[i].getHitCount();
    }
    return hitCount;
}

int Cache::getMissCount()
{
    int missCount = 0;
    for(size_t i = 0;i<cacheSets.size();i++)
    {
        missCount += cacheSets[i].getMissCount();
    }
    return missCount;
}

int Cache::getMemoryReadCount()
{
    int memoryReadCount = 0;
    for(size_t i = 0;i<cacheSets.size();i++)
    {
        memoryReadCount += cacheSets[i].getMemoryReadCount();
    }
    return memoryReadCount;
}

int Cache::getMemoryWriteCount()
{
    int memoryWriteCount = 0;
    for(size_t i = 0;i<cacheSets.size();i++)
    {
        memoryWriteCount += cacheSets[i].getMemoryWriteCount();
    }
    return memoryWriteCount;
}

