#ifndef CacheSet_h
#define CacheSet_h

#include <iostream>
#include <vector>
#include "CacheEntry.h"
using namespace std;



/************************************************************************************

The CacheSet class is meant to simulate one set of CacheSet entries
		(in an N-way CacheSet)

*************************************************************************************/

class CacheSet
{
private:
    vector<CacheEntry>   cacheLine;	// STL "array" of Cache Entries
    int	line_size;		// constructor parameter; Bytes in a CacheSet line
    // used in construction of CacheEntry
    int     associativity_factor;	// constructor parameter; N-way associativity


    // 	class variables for statistics (for this set!)
    int 	hitCount,
            missCount,
            memoryReadCount,
            memoryWriteCount;


public:
    CacheSet(int lineSize=32, int Nway=4);
    bool	hit(int tag);
    bool	readByte(int tag, int offset);		// return false if not in this set
    bool	writeByte(int tag, int offset);	// return false if not in this set
    void	loadLine(int inputTag);		// simulate loading of a cache line
    // into this set; must decide which line
    // in this set to load
    int  	getHitCount();
    int  	getMissCount();
    int	getMemoryReadCount();
    int	getMemoryWriteCount();	// return number of memory writes
};

#endif
