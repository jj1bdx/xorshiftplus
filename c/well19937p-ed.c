/*************************************************************************
Copyright:  Francois Panneton and Pierre L'Ecuyer, Université de Montréal
            Makoto Matsumoto, Hiroshima University

Notice:     This code can be used freely for personal, academic,
            or non-commercial purposes. For commercial purposes,
            please contact P. L'Ecuyer at: lecuyer@iro.UMontreal.ca

   This code can also be used under the terms of the GNU General Public
   License as published by the Free Software Foundation, either version 3
   of the License, or any later version. See the GPL licence at URL
   http://www.gnu.org/licenses

S. Harase, "Maximally equidistributed pseudorandom number generators via linear output transformations", Math. Comput. Simulation 79 (2009), no. 5, 1512--1519

**************************************************************************/
#include <sstream>
#include <cstring>
#include <cassert>
#include <stdint.h>
#include <inttypes.h>
#include <MTToolBox/AbstractGenerator.hpp>
#include <MTToolBox/AlgorithmEquidistribution.hpp>

using namespace MTToolBox;
using namespace std;

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

#define W 32
#define R 624
#define DISCARD 31
#define MASKU (0xffffffffU>>(W-DISCARD))
#define MASKL (~MASKU)
#define M1 70
#define M2 179
#define M3 449

#define MAT0POS(t,v) (v^(v>>t))
#define MAT0NEG(t,v) (v^(v<<(-(t))))
#define MAT1(v) v
#define MAT3POS(t,v) (v>>t)

#define V0            s[*p]
#define VM1Over       s[*p+M1-R]
#define VM1           s[*p+M1]
#define VM2Over       s[*p+M2-R]
#define VM2           s[*p+M2]
#define VM3Over       s[*p+M3-R]
#define VM3           s[*p+M3]
#define VRm1          s[*p-1]
#define VRm1Under     s[*p+R-1]
#define VRm2          s[*p-2]
#define VRm2Under     s[*p+R-2]

#define newV0         s[*p-1]
#define newV0Under    s[*p-1+R]
#define newV1         s[*p]
#define newVRm1       s[*p-2]
#define newVRm1Under  s[*p-2+R]

#define newVM2Over    s[*p+M2-R+1]
#define newVM2        s[*p+M2+1]

/*tempering paramater*/
#define BITMASK 0x41180000

                                        
class Well19937p : public EquidistributionCalculatable<uint32_t> {
	public:
		Well19937p(uint32_t s) {
			this->p = 0;
			WELLRNG19937p = (unsigned int (*)(uint32_t *, int *, void *))case_1;
			seed( s );
		}

    	Well19937p( const Well19937p& src ) : EquidistributionCalculatable<uint32_t>() {
			p = src.p;
			WELLRNG19937p = src.WELLRNG19937p;
			memcpy( s, src.s, sizeof s );
		}

		uint32_t generate() {
			return REV( WELLRNG19937p( s, &p, &WELLRNG19937p ) );
		}
		
		Well19937p * clone() const {
			return new Well19937p( *this );
		}

		uint32_t generate( int outBitLen ) {
			return generate() & -1 << ( 32 - outBitLen );
		}

		void seed(uint32_t value) {
			s[ 0 ] = value;
			for( int i = 1; i < R; i++ ) s[ i ] =  ( 6364136223846793005ULL * ( s[ i - 1 ] ^ ( s[ i - 1 ] >> 30) ) + value );
		}

		int bitSize() const {
			return 19937;
		}

		void add(EquidistributionCalculatable<uint32_t>& other) {
			Well19937p* that = dynamic_cast<Well19937p *>(&other);
			if( that == 0 ) throw std::invalid_argument( "the adder should have the same type as the addee." );

			for( int i = 0; i < R; i++ ) s[ ( i + p ) % R ] ^= that->s[ ( i + that->p ) % R ];
		}
		
		void setZero() {
			memset( s, 0, sizeof s );
			p = 0;
			WELLRNG19937p = (unsigned int (*)(uint32_t *, int *, void *))case_1;
		}
		
		bool isZero() const {
			if ( upper_mask & s[ p ] ) return false;
			for ( int i = 1; i < R; i++ ) if ( s[ ( p + i ) % R ] ) return false;
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
		static const uint32_t upper_mask = UINT32_C(0x80000000);
		static const uint32_t lower_mask = UINT32_C(0x7fffffff);
		uint32_t s[ R ];
		unsigned int (*WELLRNG19937p)( uint32_t *, int *, void * );
		int p;

static unsigned int case_1 ( uint32_t *s, int *p, void *f ){
   // *p == 0
   const uint32_t z0 = (VRm1Under & MASKL) | (VRm2Under & MASKU);
   const uint32_t z1 = MAT0NEG (-25, V0) ^ MAT0POS (27, VM1);
   const uint32_t z2 = MAT3POS (9, VM2) ^ MAT0POS (1, VM3);
   newV1      = z1 ^ z2;
   newV0Under = MAT1 (z0) ^ MAT0NEG (-9, z1) ^ MAT0NEG (-21, z2) ^ MAT0POS (21, newV1);
   *p = R - 1;
   *(unsigned int (**)(uint32_t *, int *, void *))f = (unsigned int (*)(uint32_t *, int *, void *))case_3;
   return (s[*p] ^ (newVM2Over & BITMASK));
}

static unsigned int case_2 ( uint32_t *s, int *p, void *f ){
   // *p == 1
   const uint32_t z0 = (VRm1 & MASKL) | (VRm2Under & MASKU);
   const uint32_t z1 = MAT0NEG (-25, V0) ^ MAT0POS (27, VM1);
   const uint32_t z2 = MAT3POS (9, VM2) ^ MAT0POS (1, VM3);
   newV1 = z1 ^ z2;
   newV0 = MAT1 (z0) ^ MAT0NEG (-9, z1) ^ MAT0NEG (-21, z2) ^ MAT0POS (21, newV1);
   *p = 0;
   *(unsigned int (**)(uint32_t *, int *, void *))f = (unsigned int (*)(uint32_t *, int *, void *))case_1;
   return (s[*p] ^ (newVM2 & BITMASK));
}

static unsigned int case_3 ( uint32_t *s, int *p, void *f ){
   // *p+M1 >= R
   const uint32_t z0 = (VRm1 & MASKL) | (VRm2 & MASKU);
   const uint32_t z1 = MAT0NEG (-25, V0) ^ MAT0POS (27, VM1Over);
   const uint32_t z2 = MAT3POS (9, VM2Over) ^ MAT0POS (1, VM3Over);
   newV1 = z1 ^ z2;
   newV0 = MAT1 (z0) ^ MAT0NEG (-9, z1) ^ MAT0NEG (-21, z2) ^ MAT0POS (21, newV1);
   (*p)--;
   if (*p + M1 < R)
      *(unsigned int (**)(uint32_t *, int *, void *))f = (unsigned int (*)(uint32_t *, int *, void *))case_5;
   return (s[*p] ^ (newVM2Over & BITMASK));
}

static unsigned int case_4 ( uint32_t *s, int *p, void *f ){
   // *p+M3 >= R
   const uint32_t z0 = (VRm1 & MASKL) | (VRm2 & MASKU);
   const uint32_t z1 = MAT0NEG (-25, V0) ^ MAT0POS (27, VM1);
   const uint32_t z2 = MAT3POS (9, VM2) ^ MAT0POS (1, VM3Over);
   newV1 = z1 ^ z2;
   newV0 = MAT1 (z0) ^ MAT0NEG (-9, z1) ^ MAT0NEG (-21, z2) ^ MAT0POS (21, newV1);
   (*p)--;
   if (*p + M3 < R)
      *(unsigned int (**)(uint32_t *, int *, void *))f = (unsigned int (*)(uint32_t *, int *, void *))case_6;
   return (s[*p] ^ (newVM2 & BITMASK));
}

static unsigned int case_5 ( uint32_t *s, int *p, void *f ){
   // *p+M2 >= R
   const uint32_t z0 = (VRm1 & MASKL) | (VRm2 & MASKU);
   const uint32_t z1 = MAT0NEG (-25, V0) ^ MAT0POS (27, VM1);
   const uint32_t z2 = MAT3POS (9, VM2Over) ^ MAT0POS (1, VM3Over);
   newV1 = z1 ^ z2;
   newV0 = MAT1 (z0) ^ MAT0NEG (-9, z1) ^ MAT0NEG (-21, z2) ^ MAT0POS (21, newV1);
   (*p)--;
   if (*p + M2 < R)
      *(unsigned int (**)(uint32_t *, int *, void *))f = (unsigned int (*)(uint32_t *, int *, void *))case_4;
	  return (s[*p] ^ (newVM2Over & BITMASK));
}

static unsigned int case_6 ( uint32_t *s, int *p, void *f ){
   // 2 <= *p <= (R - M3 - 1)
   const uint32_t z0 = (VRm1 & MASKL) | (VRm2 & MASKU);
   const uint32_t z1 = MAT0NEG (-25, V0) ^ MAT0POS (27, VM1);
   const uint32_t z2 = MAT3POS (9, VM2) ^ MAT0POS (1, VM3);
   newV1 = z1 ^ z2;
   newV0 = MAT1 (z0) ^ MAT0NEG (-9, z1) ^ MAT0NEG (-21, z2) ^ MAT0POS (21, newV1);
   (*p)--;
   if (*p == 1)
      *(unsigned int (**)(uint32_t *, int *, void *))f = (unsigned int (*)(uint32_t *, int *, void *))case_2;
   return (s[*p] ^ (newVM2 & BITMASK));
}

};

int main( int argc, char *argv[] ) {
	Well19937p well19937p(1);
	AlgorithmEquidistribution<uint32_t> eq(well19937p, 32);
	int veq[32];
	const int delta = eq.get_all_equidist(veq);
	const int bitSize = well19937p.bitSize();
	for (int i = 0; i < 32; i++) cout << "k("<< dec << setw(2) << (i + 1) << "):" << setw(5) << veq[i] << "  d(" << setw(2) << (i + 1) << "):" << setw(5) << (bitSize / (i + 1)) - veq[i] << endl;
	cout << "delta:" << delta << endl;
	return 0;
}
