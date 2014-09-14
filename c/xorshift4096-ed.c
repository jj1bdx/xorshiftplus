/*		 
 * Copyright (C) 2014 Sebastiano Vigna 
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 3 of the License, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <sstream>
#include <cstring>
#include <cassert>
#include <stdint.h>
#include <inttypes.h>
#include <MTToolBox/AbstractGenerator.hpp>
#include <MTToolBox/AlgorithmEquidistribution.hpp>
#include "reverse.h"

using namespace MTToolBox;
using namespace std;


class Xorshift4096 : public EquidistributionCalculatable<uint64_t> {
	public:
		Xorshift4096(int a, int b, int c, uint64_t s) {
			this->a = a;
			this->b = b;
			this->c = c;
			this->p = 0;
			seed( s );
		}

    	Xorshift4096( const Xorshift4096& src ) : EquidistributionCalculatable<uint64_t>() {
			a = src.a;
			b = src.b;
			c = src.c;
			p = src.p;
			memcpy( s, src.s, sizeof s );
		}

		uint64_t generate() {
			uint64_t s0 = s[ p ];
			uint64_t s1 = s[ p = ( p + 1 ) & 63 ];
			s1 ^= s1 << a;
			s1 ^= s1 >> b;
			s0 ^= s0 >> c;
			return REV( s[ p ] = s0 ^ s1 );
		}
		
		Xorshift4096 * clone() const {
			return new Xorshift4096( *this );
		}

		uint64_t generate( int outBitLen ) {
			return generate() & -1LL << ( 64 - outBitLen );
		}

		void seed(uint64_t value) {
			s[ 0 ] = value;
			for( int i = 1; i < 64; i++ ) s[ i ] =  ( 6364136223846793005ULL * ( s[ i - 1 ] ^ ( s[ i - 1 ] >> 62) ) + value );
		}

		int bitSize() const {
			return 4096;
		}

		void add(EquidistributionCalculatable<uint64_t>& other) {
			Xorshift4096* that = dynamic_cast<Xorshift4096 *>(&other);
			if( that == 0 ) throw std::invalid_argument( "the adder should have the same type as the addee." );

			for( int i = 0; i < 64; i++ ) s[ ( i + p ) % 64 ] ^= that->s[ ( i + that->p ) % 64 ];
		}
		
		void setZero() {
			memset( s, 0, sizeof s );
			p = 0;
		}
		
		bool isZero() const {
			for( int i = 0; i < 64; i++ ) if ( s[ i ] ) return false;
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
		uint64_t s[ 64 ];
		int p;
		int a, b, c;
};

int main( int argc, char *argv[] ) {
	if ( argc != 4 ) {
		fprintf(stderr, "%s A B C\n", argv[0] );
		exit(1);
	}

	Xorshift4096 xorshift4096(atoi( argv[1] ), atoi( argv[2] ), atoi( argv[3] ), 1);
	AlgorithmEquidistribution<uint64_t> eq(xorshift4096, 64);
	int veq[64];
	const int delta = eq.get_all_equidist(veq);
	const int bitSize = xorshift4096.bitSize();
	for (int i = 0; i < 64; i++) cout << "k("<< dec << setw(2) << (i + 1) << "):" << setw(5) << veq[i] << "  d(" << setw(2) << (i + 1) << "):" << setw(5) << (bitSize / (i + 1)) - veq[i] << endl;
	cout << "delta:" << delta << endl;
	return 0;
}
