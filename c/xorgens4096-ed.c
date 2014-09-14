/* 
==========================================================================
|                                                                        |
|  Copyright (C) 2004, 2006, 2008 R. P. Brent.                           |
|                                                                        |
|  This program is free software; you can redistribute it and/or         |
|  modify it under the terms of the GNU General Public License,          |
|  version 2, June 1991, as published by the Free Software Foundation.   |
|  For details see http://www.gnu.org/copyleft/gpl.html .                |
|                                                                        |
|  If you would like to use this software but the GNU GPL creates legal  |
|  problems, then please contact the author to negotiate a special       |
|  agreement.                                                            |
|                                                                        |
==========================================================================

*/

#include <sstream>
#include <cstring>
#include <cassert>
#include <stdint.h>
#include <inttypes.h>
#include <MTToolBox/AbstractGenerator.hpp>
#include <MTToolBox/AlgorithmEquidistribution.hpp>
#include "xorgens.h"
#include "reverse.h"

using namespace MTToolBox;
using namespace std;


#define UINT64 (sizeof(UINT)>>3)
#define UINT32 (1 - UINT64) 

#define wlen (64*UINT64 +  32*UINT32)
#define r    (64*UINT64 + 128*UINT32)
#define s    (53*UINT64 +  95*UINT32)
#define a    (33*UINT64 +  17*UINT32)
#define b    (26*UINT64 +  12*UINT32)
#define c    (27*UINT64 +  13*UINT32)
#define d    (29*UINT64 +  15*UINT32)
#define ws   (27*UINT64 +  16*UINT32) 

class Xorgens4096 : public EquidistributionCalculatable<uint64_t> {
	public:
		Xorgens4096(uint64_t v) {
			this->p = 0;
			seed( v );
		}

    	Xorgens4096( const Xorgens4096& src ) : EquidistributionCalculatable<uint64_t>() {
			p = src.p;
			memcpy( x, src.x, sizeof x );
		}

		uint64_t generate() {
			UINT t, v;
  
			t = x[p = (p+1)&(r-1)];            /* Assumes that r is a power of two */
			v = x[(p+(r-s))&(r-1)];            /* Index is (i-s) mod r */
			t ^= t<<a;  t ^= t>>b;             /* (I + L^a)(I + R^b) */
			v ^= v<<c;  v ^= v>>d;             /* (I + L^c)(I + R^d) */
			x[p] = (v ^= t);                   /* Update circular array */
			return REV(v);
		}
		
		Xorgens4096 * clone() const {
			return new Xorgens4096( *this );
		}

		uint64_t generate( int outBitLen ) {
			return generate() & -1LL << ( 64 - outBitLen );
		}

		void seed(uint64_t value) {
			x[ 0 ] = value;
			for( int i = 1; i < 64; i++ ) x[ i ] =  ( 6364136223846793005ULL * ( x[ i - 1 ] ^ ( x[ i - 1 ] >> 62) ) + value );
		}

		int bitSize() const {
			return 4096;
		}

		void add(EquidistributionCalculatable<uint64_t>& other) {
			Xorgens4096* that = dynamic_cast<Xorgens4096 *>(&other);
			if( that == 0 ) throw std::invalid_argument( "the adder should have the same type as the addee." );

			for( int i = 0; i < 64; i++ ) x[ ( i + p ) % 64 ] ^= that->x[ ( i + that->p ) % 64 ];
		}
		
		void setZero() {
			memset( x, 0, sizeof x );
			p = 0;
		}
		
		bool isZero() const {
			for( int i = 0; i < 64; i++ ) if ( x[ i ] ) return false;
			return true;
		}

		void setUpParam(AbstractGenerator<uint64_t>& ab) {
			assert(false);
		}

		const std::string getHeaderString() {
			return "";
		}

		const std::string getParamString() {
			return "";
		}
	private:
		uint64_t x[ 64 ];
		int p;
};

int main( int argc, char *argv[] ) {
	Xorgens4096 xorgens4096(1);
	AlgorithmEquidistribution<uint64_t> eq(xorgens4096, 64);
	int veq[64];
	const int delta = eq.get_all_equidist(veq);
	const int bitSize = xorgens4096.bitSize();
	for (int i = 0; i < 64; i++) cout << "k("<< dec << setw(2) << (i + 1) << "):" << setw(5) << veq[i] << "  d(" << setw(2) << (i + 1) << "):" << setw(5) << (bitSize / (i + 1)) - veq[i] << endl;
	cout << "delta:" << delta << endl;
	return 0;
}
