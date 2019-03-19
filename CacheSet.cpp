
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
        cacheLine.push_back(CacheEntry(line_size));

    hitCount  = 0;
    missCount = 0;
    memoryReadCount  = 0;
    memoryWriteCount = 0;
}



bool CacheSet::hit(int tag)
{
    bool haveHit = false;
    int  lineNumber;  	// for searching through the set


    for (int lineNumber=0; lineNumber < associativity_factor; lineNumber ++)
        if (cacheLine[lineNumber].hit(tag))
            return true;

    return false;
}



bool CacheSet::readByte(int tag, int offset)
{
// to be implemented
}


bool CacheSet::writeByte(int tag, int offset)
{
// to be implemented
}

void CacheSet::loadLine(int inputTag)
{
// to be implemented
}



int CacheSet::getHitCount()
{
// to be implemented
}



int CacheSet::getMissCount()
{
// to be implemented
}


int CacheSet::getMemoryReadCount()
{
// to be implemented
}



int CacheSet::getMemoryWriteCount()
{
// to be implemented
}


