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
#include <stdint.h>
#include <inttypes.h>
#include <MTToolBox/AbstractGenerator.hpp>
#include <MTToolBox/AlgorithmEquidistribution.hpp>
#include "reverse.h"

using namespace MTToolBox;
using namespace std;


class Xorshift64 : public EquidistributionCalculatable<uint64_t> {
	public:
		Xorshift64(int type, int a, int b, int c, uint64_t seed) {
			this->type = type;
			this->a = a;
			this->b = b;
			this->c = c;
			this->x = seed;
		}

		uint64_t generate() {
			switch(type) {
				case 0: x ^= x << a; x ^= x >> b; x ^= x << c; break; // X1
				case 1: x ^= x >> a; x ^= x << b; x ^= x >> c; break; // X3
				case 2: x ^= x << c; x ^= x >> b; x ^= x << a; break; // X2
				case 3: x ^= x >> c; x ^= x << b; x ^= x >> a; break; // X4
				case 4: x ^= x << a; x ^= x << c; x ^= x >> b; break; // X5
				case 5: x ^= x >> a; x ^= x >> c; x ^= x << b; break; // X6
				case 6: x ^= x >> b; x ^= x << a; x ^= x << c; break; // X7
				case 7: x ^= x << b; x ^= x >> a; x ^= x >> c; break; // X8
			}
			return REV( x ); // This is actually not necessary, as conjugates are reversed, but it's useful as a sanity check.
		}
		
		Xorshift64 * clone() const {
			return new Xorshift64(type, a, b, c, x);
		}

		uint64_t generate( int outBitLen ) {
			return generate() & -1LL << ( 64 - outBitLen );
		}

		void seed(uint64_t value) {
			x = value;
		}
		int bitSize() const {
			return 64;
		}

		void add(EquidistributionCalculatable<uint64_t>& other) {
			Xorshift64* that = dynamic_cast<Xorshift64 *>(&other);
			if( that == 0 ) throw std::invalid_argument( "the adder should have the same type as the addee." );

			x ^= that->x;
		}
		
		void setZero() {
			x = 0;
		}
		
		bool isZero() const {
			return x == 0;
		}

		void setUpParam(AbstractGenerator<uint64_t>& ab) {
			x = ab.generate();
		}

		const std::string getHeaderString() {
			return "Xorshift64";
		}

		const std::string getParamString() {
			return "";
		}
	private:
		uint64_t x;
		int type, a, b, c;
		void (*next)();

};

int main( int argc, char *argv[] ) {
	if ( argc != 5 ) {
		fprintf(stderr, "%s ALGORITHM A B C\n", argv[0] );
		exit(1);
	}

	Xorshift64 xorshift64(atoi( argv[1] ), atoi( argv[2] ), atoi( argv[3] ), atoi( argv[4] ), 1);
	AlgorithmEquidistribution<uint64_t> eq(xorshift64, 64);
	int veq[64];
	const int delta = eq.get_all_equidist(veq);
	const int bitSize = xorshift64.bitSize();
	for (int i = 0; i < 64; i++) cout << "k("<< dec << setw(2) << (i + 1) << "):" << setw(5) << veq[i] << "  d(" << setw(2) << (i + 1) << "):" << setw(5) << (bitSize / (i + 1)) - veq[i] << endl;
	cout << "delta:" << delta << endl;
	return 0;
}
