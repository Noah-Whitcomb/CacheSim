// John Gaboriault-Whitcomb
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

extern ofstream outputfile;

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
    bool	hit(int tag, int& indexOfHit);
    bool	readByte(int tag, int offset);	// return false if not in this set
    bool	writeByte(int tag, int offset); 	// return false if not in this set
    void	loadLine(int inputTag, int offset, bool write);		// simulate loading of a cache line
    // into this set; must decide which line
    // in this set to load
    int  	getHitCount() {return hitCount;}
    int  	getMissCount() {return missCount;}
    int	getMemoryReadCount() {return memoryReadCount;}
    int	getMemoryWriteCount() {return memoryWriteCount;}	// return number of memory writes
    void incHitCount() {hitCount++;}
    void incMissCount() {missCount++;}
    void incMemoryReadCount() {memoryReadCount++;}
    void incMemoryWriteCount() {memoryWriteCount++;}
};

#endif
