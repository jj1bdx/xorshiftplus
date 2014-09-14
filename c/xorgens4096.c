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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#ifdef TESTU01
#include <unif01.h>
#include <bbattery.h>
#endif


#include "xorgens.h"

  /* 32-bit or 64-bit integer random number generator 
     with period at least 2**4096-1.
     
     It is assumed that "UINT" is a 32-bit or 64-bit integer 
     (see typedef statements in xorgens.h).
     
     xor4096i should be called exactly once with nonzero seed, and
     thereafter with zero seed.  
     
     One random number uniformly distributed in [0..2**wlen) is returned,
     where wlen = 8*sizeof(UINT) = 32 or 64.

     R. P. Brent, 20060628.
  */

  /* UINT64 is TRUE if 64-bit UINT,
     UINT32 is TRUE otherwise (assumed to be 32-bit UINT). */
     
static UINT w, weyl;

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

static UINT x[r];

UINT xor4096i() {
  static int i = -1;
  UINT t, v;
  
  t = x[i = (i+1)&(r-1)];            /* Assumes that r is a power of two */
  v = x[(i+(r-s))&(r-1)];            /* Index is (i-s) mod r */
  t ^= t<<a;  t ^= t>>b;             /* (I + L^a)(I + R^b) */
  v ^= v<<c;  v ^= v>>d;             /* (I + L^c)(I + R^d) */
  x[i] = (v ^= t);                   /* Update circular array */
  w += weyl;                         /* Update Weyl generator */
  return (v + (w^(w>>ws)));          /* Return combination */
}

UREAL xor4096r(UINT seed)

  {
  /* 64-bit or 32-bit real random number generator 
     with period at least 2**4096-1.
     
     It is assumed that "UINT" is a 32-bit or 64-bit integer and "UREAL"
     is "double" or "float". If "double" this is an IEEE standard
     floating-point number with 53 bits in the fraction; if "single" it 
     has 24 bits in the fraction (including 1 implicit bit in each case).
     
     In the 64-bit integer case, the method used is to call xor4096i to get
     64 random bits, then the high 53 (for double) or 24 bits (for float)
     are scaled to the open interval (0.0, 1.0), except that they are
     discarded if all zero.

     In the 32-bit integer case, one or two calls to xor4096i are made to
     get 32 or 64 random bits, some are discarded, and the remaining bits
     (if nonzero) are scaled to the open interval (0.0, 1.0).  

     xor4096r should be called exactly once with nonzero seed, and
     thereafter with zero seed.

     One random number of type UREAL is returned per call.
     
     The results be should uniformly distributed in (0.0, 1.0) to the
     resolution of the floating-point system (0.5**53 or 0.5**24).  

     The results are never exactly 0.0 or 1.0.

     R. P. Brent, 20060628.
     */
     
#define UINT64 (sizeof(UINT)>>3)
#define UINT32 (1 - UINT64) 
#define UREAL64 (sizeof(UREAL)>>3)
#define UREAL32 (1 - UREAL64)

/* sr = number of bits discarded = 11 for double, 40 or 8 for float */
 
#define sr (11*UREAL64 +(40*UINT64 + 8*UINT32)*UREAL32)

/* ss (used for scaling) is 53 or 21 for double, 24 for float */

#define ss ((53*UINT64 + 21*UINT32)*UREAL64 + 24*UREAL32)

/* SCALE is 0.5**ss, SC32 is 0.5**32 */

#define SCALE ((UREAL)1/(UREAL)((UINT)1<<ss)) 
#define SC32  ((UREAL)1/((UREAL)65536*(UREAL)65536)) 

  UREAL res;
  
  res = (UREAL)0; 
  while (res == (UREAL)0)               /* Loop until nonzero result.   */
    {                                   /* Usually only one iteration . */
    res = (UREAL)(xor4096i()>>sr);  /* Discard sr random bits.  */
    seed = (UINT)0;                     /* Zero seed for next time. */
    if (UINT32 && UREAL64)              /* Need another call to xor4096i. */
      res += SC32*(UREAL)xor4096i();/* Add low-order 32 bits. */
    }
  return (SCALE*res);                   /* Return result in (0.0, 1.0). */  
}


#ifdef REVERSE

static __inline uint64_t reverse( uint64_t x ) {
	x = ((x >> 1) & 0x5555555555555555ULL) | ((x & 0x5555555555555555ULL) << 1);
	x = ((x >> 2) & 0x3333333333333333ULL) | ((x & 0x3333333333333333ULL) << 2);
	x = ((x >> 4) & 0x0F0F0F0F0F0F0F0FULL) | ((x & 0x0F0F0F0F0F0F0F0FULL) << 4);
	x = ((x >> 8) & 0x00FF00FF00FF00FFULL) | ((x & 0x00FF00FF00FF00FFULL) << 8);
	x = ((x >> 16) & 0x0000FFFF0000FFFFULL ) | ((x & 0x0000FFFF0000FFFFULL) << 16);
	return ( x >> 32 ) | ( x << 32 );
}

#define NAME "xorgens4096-rev"
#define REV(x) (reverse(x))
#else
#define NAME "xorgens4096" 
#define REV(x) (x)
#endif

#define NORM_64 ( ( 1./4 ) / ( 1LL << 62 ) )


/* True if the lower part of y has already been returned. */
static int lower;

static uint64_t y;

/* Note that this function returns a 32-bit number. */
unsigned long xorgens( void *unused0, void *unused1 ) {
	if ( lower ^= 1 ) return (uint32_t)y;
	const uint32_t result = y >> 32;
	y = REV( xor4096i() );
	return result;
}

double xorgens01( void *unused0, void *unused1 ) {
	if ( lower ) y = REV( xor4096i() ); // Refresh x (lower part has already been used).
	const double result = y * NORM_64;
	y = REV( xor4096i() );
	lower = 0;
	return result;
}

void write_state( void *unused ) {
	printf ( "\n" );
}

uint64_t strtoull_check( char *p ) {
	const uint64_t result = strtoull( p, NULL, 0 );
	if ( errno != 0 ) {
		fprintf(stderr, "Error while parsing seed: %s\n", strerror( errno ) );
		exit( 1 );
	}
	if ( 1 << 10 < result && result < 1ULL << 32 ) fprintf(stderr, "Suspiciosly 32-bit value while parsing seed: %llu\n", (unsigned long long)result );
	return result;
}


int main(int argc, char *argv[]) {
	if ( argc != r + 2 ) {
		fprintf(stderr, "%s SEED (%lu 64-bit integers)\n", argv[0], r + 1 );
		exit(1);
	}
	
	w = strtoull_check( argv[1] );
	for( int i = 0; i < r; i++ ) x[i] = strtoull_check( argv[i+2] );
	weyl = ((((UINT)0x61c88646)<<16)<<16) + (UINT)0x80b583eb;

#ifdef TESTU01
	unif01_Gen gen;
	gen.name = NAME;
	gen.Write = write_state;
	gen.GetBits = xorgens;
	gen.GetU01 = xorgens01;
	TESTU01( &gen );
#else
	assert(freopen(NULL, "wb", stdout));

	for(;;) {
		const uint32_t z = xorgens( NULL, NULL );
		fwrite(&z, sizeof z, 1, stdout);
	}
#endif

	return 0;
}
