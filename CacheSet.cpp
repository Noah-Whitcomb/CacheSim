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
        if (cacheLine[lineNumber].hit(tag) && !cacheLine[lineNumber].isDirty()) {
            indexOfHit = lineNumber;
            cacheLine[lineNumber].setLRU_counter(0);
            return true;
        }
    }

    return false;
}


bool CacheSet::readByte(int tag, int offset)
{
    // if there is a hit, return true
    // if not, load byte into the least recently used block
    int indexofHit;
    if(hit(tag, indexofHit))
    {
        // reset the LRU counter of the recently hit cacheEntry
        // increment all other counters
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
        loadLine(tag, offset, false);
        return false;
    }

}


bool CacheSet::writeByte(int tag, int offset)
{
    int indexofHit;
    if(hit(tag, indexofHit))
    {
        // reset the LRU counter of the recently hit cacheEntry
        // increment all other counters
        // this stays the same for writes - you are likely
        // to use data you just wrote
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
        // if there is a hit, set the block to dirty
        // this makes sure it is written to main memory before being replaced
        cacheLine[indexofHit].setDirty();
        return true;
    }
    else
    {
        loadLine(tag, offset, true);
        return false;
    }
}

void CacheSet::loadLine(int inputTag, int offset, bool write)
{
    // figure out which line to load to based on LRU
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

    // loadline if space permits (it always will)
    bool did_write = false;
    if(cacheLine[indexToReplace].readByte(offset))
    {
        if(cacheLine[indexToReplace].isDirty())
        {
            // write this block back to main memory before replacing it
            // there isn't a main memory in this project so nothing happens here
        }
        cacheLine[indexToReplace].loadLine(inputTag);
        did_write = true;

        // if this load is a write, set dirty to true
        // if it is a read, make sure dirty is set to false
        if(write)
        {
            cacheLine[indexToReplace].setDirty();
        }
        else
        {
            cacheLine[indexToReplace].resetDirty();
        }
    }

    // take care of all LRU counters
    for(size_t i = 0;i<cacheLine.size();i++)
    {
        if(i == indexToReplace && did_write)
        {
            cacheLine[indexToReplace].setLRU_counter(0);
        }
        else
        {
            cacheLine[i].incLRU_counter();
        }
    }
}



