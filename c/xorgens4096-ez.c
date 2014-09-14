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

#undef c
#undef b

int main(int argc, char *argv[] ) {
	if ( argc != 3 ) {
		fprintf(stderr, "%s NUMBER WINDOW\n", argv[0] );
		exit(1);
	}

	const int n = atoi( argv[1] );
	const int k = atoi( argv[2] );
	unsigned long long c[ n + k ];
	memset( c, 0, sizeof c );
	weyl = ((((UINT)0x61c88646)<<16)<<16) + (UINT)0x80b583eb;
	
	for( int b = 0; b < 4096; b++ ) {
		memset( x, 0, sizeof x );
		w = 0;
		x[ b / 64 ] = 1ULL << b % 64;
	
		for( int i = 0; i < n; i++ ) {	
			const int t = __builtin_popcountll( xor4096i() );
			for( int j = 0; j < k; j++ ) c[ i + j ] += t;
		}
	}

	double norm = 1. / ( 4096 * k * 64 );
	for( int i = k; i < n; i++ ) printf( "%f\n", c[ i ] * norm );
}
