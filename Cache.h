#ifndef Cache_h
#define Cache_h
#include <vector>
#include "CacheSet.h"
using namespace std;


class Cache
{
private:
    vector<CacheSet>   cacheSets;	// "array" of cache sets
    int	number_of_sets;
    int	line_size;		// constructor parameter; Bytes in a cache line
    int     associativity_factor;	// constructor parameter; N-way associativity

    // 	class variables for extracting set number, offset, and tag
    int 	bits_in_set;		// computed, assumes line_size is a power of 2
    int 	bits_in_offset;		// computed, assumes line_size is a power of 2

//	power_of_two returns the log base 2 of the input value.
//		It the log is not an integer,
//		returns a negative value  of some kind.
    int	power_of_two(int value);

//	splitAddress splits a given address into 3 fields:  tag, setNumber, and offset
    void	splitAddress( int address,
                          int &tag, int &setNumber, int &offset);


public:
    Cache(int setCount=8, int associativity=4, int lineSize=16);

    bool   	readByte(int address);
    bool	writeByte(int address);

    int  	getHitCount();
    int  	getMissCount();
    int	getMemoryReadCount();
    int	getMemoryWriteCount();	// return number of memory writes
};

#endif
