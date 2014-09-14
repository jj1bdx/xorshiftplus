#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <dieharder/libdieharder.h>

// Comment/uncomment to get a xorshift64* generator and a reverse generator.
#define STAR32
#define REVERSE

/* The internal state of the generator. */
static uint64_t x = 0x1LL;
/* The current 64-bit value output by the generator (this is not x if STAR32 is defined.) */
static uint64_t y;
static int AA, BB, CC;


#ifdef STAR32
// Composed with M_32.
const int64_t MM = 2685821657736338717LL;

#ifdef REVERSE

static __inline uint64_t reverse( uint64_t x ) {
        x = ((x >> 1) & 0x5555555555555555ULL) | ((x & 0x5555555555555555ULL) << 1);
        x = ((x >> 2) & 0x3333333333333333ULL) | ((x & 0x3333333333333333ULL) << 2);
        x = ((x >> 4) & 0x0F0F0F0F0F0F0F0FULL) | ((x & 0x0F0F0F0F0F0F0F0FULL) << 4);
        x = ((x >> 8) & 0x00FF00FF00FF00FFULL) | ((x & 0x00FF00FF00FF00FFULL) << 8);
        x = ((x >> 16) & 0x0000FFFF0000FFFFULL ) | ((x & 0x0000FFFF0000FFFFULL) << 16);
        return ( x >> 32 ) | ( x << 32 );
}

#define NAME "xorshiftlcg-rev"
#define REV(x) (reverse(x))
#else
#define NAME "xorshiftlcg"
#define REV(x) (x)
#endif


/* Panneton/L’Ecuyer

X1 = (I+Lc)(I+Rb)(I+La),
X2 = (I+La)(I+Rb)(I+Lc),

X3 = (I+Rc)(I+Lb)(I+Ra),
X4 = (I+Ra)(I+Lb)(I+Rc),

X5 = (I+Rb)(I+Lc)(I+La),
X6 = (I+Lb)(I+Ra)(I+Rc),

X7 = (I+Lc)(I+La)(I+Rb),
X8 = (I+Ra)(I+Rc)(I+Lb),
*/

void next0() { x ^= x << AA; x ^= x >> BB; x ^= x << CC; y = REV( x * MM ); }  // X1
void next1() { x ^= x >> AA; x ^= x << BB; x ^= x >> CC; y = REV( x * MM );  } // X3
void next2() { x ^= x << CC; x ^= x >> BB; x ^= x << AA; y = REV( x * MM );  } // X2
void next3() { x ^= x >> CC; x ^= x << BB; x ^= x >> AA; y = REV( x * MM );  } // X4
void next4() { x ^= x << AA; x ^= x << CC; x ^= x >> BB; y = REV( x * MM );  } // X5
void next5() { x ^= x >> AA; x ^= x >> CC; x ^= x << BB; y = REV( x * MM );  } // X6
void next6() { x ^= x >> BB; x ^= x << AA; x ^= x << CC; y = REV( x * MM );  } // X7
void next7() { x ^= x << BB; x ^= x >> CC; x ^= x >> AA; y = REV( x * MM );  } // X8
#else
#define NAME "xorshift"
void next0() { x ^= x << AA; x ^= x >> BB; x ^= x << CC; y = x; }
void next1() { x ^= x >> AA; x ^= x << BB; x ^= x >> CC; y = x;  }
void next2() { x ^= x << CC; x ^= x >> BB; x ^= x << AA; y = x;  }
void next3() { x ^= x >> CC; x ^= x << BB; x ^= x >> AA; y = x;  }
void next4() { x ^= x << AA; x ^= x << CC; x ^= x >> BB; y = x;  }
void next5() { x ^= x >> AA; x ^= x >> CC; x ^= x << BB; y = x;  }
void next6() { x ^= x >> BB; x ^= x << AA; x ^= x << CC; y = x;  }
void next7() { x ^= x << BB; x ^= x >> CC; x ^= x >> AA; y = x;  }
#endif

/* True if the lower part of y has already been returned. */
static int lower;
static void (*next)();

static unsigned long int xorshift_get (void *unused);
static double xorshift_get_double (void *unused);
static void xorshift_set (void *unused, unsigned long int s);

static unsigned long int xorshift_get (void *unused) {
	if ( lower ^= 1 ) return (uint32_t)y;
	const uint32_t result = y >> 32;
	next();
	return result;
}

#define NORM_64 ( ( 1./4 ) / ( 1LL << 62 ) )

static double xorshift_get_double (void *unused) {
	if ( lower ) next(); // Refresh x (lower part has already been used).
	const double result = y * NORM_64;
	next();
	lower = 0;
	return result;
}

void xorshift_set_algo( int algo, int AAA, int BBB, int CCC, uint64_t seed ) {
	switch( algo ) {
		case 0: next = next0; break;
		case 1: next = next1; break;
		case 2: next = next2; break;
		case 3: next = next3; break;
		case 4: next = next4; break;
		case 5: next = next5; break;
		case 6: next = next6; break;
		case 7: next = next7; break;
	}

	AA = AAA;
	BB = BBB;
	CC = CCC;
	x = seed;
	// printf( "Let A=%d B=%d C=%d algo=%d seed=%llu\n", AA, BB, CC, algo, x );
	next(); // So y has a sensible initial value.
}

static void xorshift_set (void *unused, unsigned long int s) {
	// No-op--use xorshift_set_algo().
}

static const gsl_rng_type xorshift_type = {
 NAME,
 UINT_MAX,                      /* RAND_MAX */
 0,                             /* RAND_MIN */
 0,
 xorshift_set,
 xorshift_get,
 xorshift_get_double};

const gsl_rng_type *gsl_rng_xorshift = &xorshift_type;
