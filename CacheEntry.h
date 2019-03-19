// header file for cache Entry for CSCI 5814 Spring 2010

#ifndef cacheEntry_h
#define cacheEntry_h
#include <ostream>
#include <iostream>
using namespace std;


class CacheEntry
{
private:
    int     lineSize;
    int     tag;
    bool    valid;
    bool	dirty;
    int     LRU_counter;


public:
    CacheEntry(int lineSize=32);		// constructor with default linesize


//  hit()   returns true if a cache hit is made on the given tag
    bool    hit(int tag) const;


// readByte()	simulates reading a Byte value from this cache entry
//		the offset of  the data read must be <= cache line size
    bool  	readByte(int offset) const;


// writeByte()	writes a Byte value to this cache entry
//		the offset of data read must be <= cache line size
    bool	writeByte (int offset);


// isDirty()	returns the value of the dirty flag
    bool	isDirty() const;

// setDirty()	sets the dirty flag to true
    void	setDirty();

// resetDirty()	resets the dirty flag to false
    void	resetDirty();


// loadLine()	loads a line of cache (actually sets the tag and the valid bit)
    void	loadLine(int inputTag);


//  print function for the CacheEntry
    friend  std::ostream& operator<< (std::ostream&, const CacheEntry&);


// getLRU_counter returns the counter for purposes of implementing a LRU replacement
//			algorithm;  Something outside must operate on this.
    int	getLRU_counter() const;


// setLRU_counter sets the counter for purposes of implementing a LRU replacement
//			algorithm;  Something outside must operate on this.
    void	setLRU_counter(int value);


// incLRU_counter increments the counter.  No checking is preformed .
    void	incLRU_counter();


// decLRU_counter decrements the counter.  No checking is preformed .
    void	decLRU_counter();

};

#endif
