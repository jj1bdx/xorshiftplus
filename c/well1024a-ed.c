/* ***************************************************************************** */
/* Copyright:      Francois Panneton and Pierre L'Ecuyer, University of Montreal */
/*                 Makoto Matsumoto, Hiroshima University                        */
/* Notice:         This code can be used freely for personal, academic,          */
/*                 or non-commercial purposes. For commercial purposes,          */
/*                 please contact P. L'Ecuyer at: lecuyer@iro.UMontreal.ca       */
/* ***************************************************************************** */

#include <sstream>
#include <cstring>
#include <cassert>
#include <stdint.h>
#include <inttypes.h>
#include <MTToolBox/AbstractGenerator.hpp>
#include <MTToolBox/AlgorithmEquidistribution.hpp>

using namespace MTToolBox;
using namespace std;

#define W 32
#define R 32
#define M1 3
#define M2 24
#define M3 10

#define MAT0POS(t,v) (v^(v>>t))
#define MAT0NEG(t,v) (v^(v<<(-(t))))
#define Identity(v) (v)

#define V0            s[p                   ]
#define VM1           s[(p+M1) & 0x0000001fU]
#define VM2           s[(p+M2) & 0x0000001fU]
#define VM3           s[(p+M3) & 0x0000001fU]
#define VRm1          s[(p+31) & 0x0000001fU]
#define newV0         s[(p+31) & 0x0000001fU]
#define newV1         s[p                   ]

#ifdef REVERSE

static __inline uint32_t reverse( uint32_t x ) {
	x = ((x >> 1) & 0x55555555U) | ((x & 0x55555555U) << 1);
	x = ((x >> 2) & 0x33333333U) | ((x & 0x33333333U) << 2);
	x = ((x >> 4) & 0x0F0F0F0FU) | ((x & 0x0F0F0F0FU) << 4);
	x = ((x >> 8) & 0x00FF00FFU) | ((x & 0x00FF00FFU) << 8);
	return ( x >> 16) | (x << 16 );
}

#define REV(x) (reverse(x))
#else
#define REV(x) (x)
#endif
                                        
class Well1024a : public EquidistributionCalculatable<uint32_t> {
	public:
		Well1024a(uint32_t s) {
			this->p = 0;
			seed( s );
		}

    	Well1024a( const Well1024a& src ) : EquidistributionCalculatable<uint32_t>() {
			p = src.p;
			memcpy( s, src.s, sizeof s );
		}

		uint32_t generate() {
			const uint32_t	z0    = VRm1;
			const uint32_t z1    = Identity(V0)       ^ MAT0POS (8, VM1);
			const uint32_t z2    = MAT0NEG (-19, VM2) ^ MAT0NEG(-14,VM3);
			newV1 = z1                 ^ z2; 
			newV0 = MAT0NEG (-11,z0)   ^ MAT0NEG(-7,z1)    ^ MAT0NEG(-13,z2) ;
			p = (p + 31) & 0x0000001fU;
			return REV( s[p] );
		}
		
		Well1024a * clone() const {
			return new Well1024a( *this );
		}

		uint32_t generate( int outBitLen ) {
			return generate() & -1 << ( 32 - outBitLen );
		}

		void seed(uint32_t value) {
			s[ 0 ] = value;
			for( int i = 1; i < 32; i++ ) s[ i ] =  ( 6364136223846793005ULL * ( s[ i - 1 ] ^ ( s[ i - 1 ] >> 30) ) + value );
		}

		int bitSize() const {
			return 1024;
		}

		void add(EquidistributionCalculatable<uint32_t>& other) {
			Well1024a* that = dynamic_cast<Well1024a *>(&other);
			if( that == 0 ) throw std::invalid_argument( "the adder should have the same type as the addee." );

			for( int i = 0; i < 32; i++ ) s[ ( i + p ) % 32 ] ^= that->s[ ( i + that->p ) % 32 ];
		}
		
		void setZero() {
			memset( s, 0, sizeof s );
			p = 0;
		}
		
		bool isZero() const {
			for( int i = 0; i < 32; i++ ) if ( s[ i ] ) return false;
			return true;
		}

		void setUpParam(AbstractGenerator<uint32_t>& ab) {
			assert(false);
		}

		const std::string getHeaderString() {
			return "";
		}

		const std::string getParamString() {
			return "";
		}
	private:
		uint32_t s[ 32 ];
		int p;
};

int main( int argc, char *argv[] ) {
	Well1024a well1024a(1);
	AlgorithmEquidistribution<uint32_t> eq(well1024a, 32);
	int veq[32];
	const int delta = eq.get_all_equidist(veq);
	const int bitSize = well1024a.bitSize();
	for (int i = 0; i < 32; i++) cout << "k("<< dec << setw(2) << (i + 1) << "):" << setw(5) << veq[i] << "  d(" << setw(2) << (i + 1) << "):" << setw(5) << (bitSize / (i + 1)) - veq[i] << endl;
	cout << "delta:" << delta << endl;
	return 0;
}
