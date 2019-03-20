// John Gaboriault-Whitcomb
#include "CacheSet.h"
using namespace std;

/************************************************************************************
The CacheSet class is meant to simulate one set of CacheSet entries (in an N-way CacheSet)

*************************************************************************************/

//	constructor
CacheSet::CacheSet(int lineSize, int Nway)
{
    line_size = lineSize;

    associativity_factor = Nway;
    // create a line for each entry in the set
    for (int i=0; i < Nway; i++)
    {
        cacheLine.emplace_back(CacheEntry(line_size));
    }

    hitCount  = 0;
    missCount = 0;
    memoryReadCount  = 0;
    memoryWriteCount = 0;
}



bool CacheSet::hit(int tag, int& indexOfHit)
{
    bool haveHit = false;
    //int  lineNumber;  	// for searching through the set


    for (int lineNumber=0; lineNumber < associativity_factor; lineNumber ++)
    {
        if (cacheLine[lineNumber].hit(tag)) {
            indexOfHit = lineNumber;
            cacheLine[lineNumber].setLRU_counter(0);
            return true;
        }
    }

    return false;
}



bool CacheSet::readByte(int tag, int offset)
{
    // for level 0 the size of each set is 1
    // for set associative cache there are multiple options per set
    // if there is a hit, return true
    // if not, load byte into the least recently used block
    int indexofHit;
    if(hit(tag, indexofHit) && cacheLine[indexofHit].readByte(offset))
    {
        for(size_t i = 0;i<cacheLine.size();i++)
        {
            if(i == indexofHit)
            {
                cacheLine[i].setLRU_counter(0);
            }
            else
            {
                cacheLine[i].incLRU_counter();
            }
        }
        return true;
    }
    else
    {
        loadLine(tag);
        return false;
    }

}


bool CacheSet::writeByte(int tag, int offset)
{
// to be implemented
}

void CacheSet::loadLine(int inputTag)
{
    // figure out which line to write to based on LRU
    int leastRecentlyUsed = cacheLine[0].getLRU_counter();
    int indexToReplace = 0;
    for(size_t i = 0;i<cacheLine.size();i++)
    {
        if(leastRecentlyUsed < cacheLine[i].getLRU_counter())
        {
            leastRecentlyUsed = cacheLine[i].getLRU_counter();
            indexToReplace = i;
        }
    }
    cacheLine[indexToReplace].loadLine(inputTag);

    // take care of all LRU counters
    for(size_t i = 0;i<cacheLine.size();i++)
    {
        if(i == indexToReplace)
        {
            cacheLine[indexToReplace].setLRU_counter(0);
        }
        else
        {
            cacheLine[i].incLRU_counter();
        }
    }
}



