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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include "reverse.h"

#ifdef TESTU01
#include <unif01.h>
#include <bbattery.h>
#endif

/* The internal state of the generator. */
static uint64_t x = 0x1LL;

/* The current state of the generator. */
static uint64_t s[ 16 ];

/* The current 64-bit value output by the generator (this is not x if STAR32/STAR8/STAR2 is defined.) */
static uint64_t y;

/* The three shifts. */
static int A, B, C;

#ifdef STAR32
// Composed with M_32.
const int64_t M = 2685821657736338717LL;
#endif

#ifdef STAR8
// Composed with M_8.
const int64_t M = 1181783497276652981LL;
#endif

#ifdef STAR2
// Composed with M_2.
const int64_t M = 8372773778140471301LL;
#endif

static int p;
				
void next0() { 
	uint64_t s0 = s[ p ]; 
	uint64_t s1 = s[ p = ( p + 1 ) & 15 ];
	s1 ^= s1 << A;
#if defined(ADD)
	y = ( s[ p ] = ( s1 ^ s0 ^ ( s1 >> B ) ^ ( s0 >> C ) ) ) + s0;
#else
	y = ( s[ p ] = ( s1 ^ s0 ^ ( s1 >> B ) ^ ( s0 >> C ) ) ) * M;
#endif
}

static void (*next)();

int main(int argc, char *argv[] ) {
	if ( argc != 7 ) {
		fprintf(stderr, "%s ALGORITHM A B C NUMBER WINDOW\n", argv[0] );
		exit(1);
	}

	if ( atoi( argv[1] ) != 0 ) abort();
	next = next0;

	A = atoi( argv[2] );
	B = atoi( argv[3] );
	C = atoi( argv[4] );

	const int n = atoi( argv[5] );
	const int k = atoi( argv[6] );
	unsigned long long c[ n + k ];
	memset( c, 0, sizeof c );
	
	for( int b = 0; b < 1024; b++ ) {
		memset( s, 0, sizeof s );
		s[ b / 64 ] = 1ULL << b % 64;
	
		for( int i = 0; i < n; i++ ) {	
			next();
			const int t = __builtin_popcountll( y );
			for( int j = 0; j < k; j++ ) c[ i + j ] += t;
		}
	}

	double norm = 1. / ( 1024 * k * 64 );
	for( int i = k; i < n; i++ ) printf( "%f\n", c[ i ] * norm );
}
