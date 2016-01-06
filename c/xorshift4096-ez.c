/*		 
 * Copyright (C) 2014-2015 Sebastiano Vigna 
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
static uint64_t s[ 64 ];

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
	uint64_t s1 = s[ p = ( p + 1 ) & 63 ];
	s1 ^= s1 << A;
	s1 ^= s1 >> B;
	s0 ^= s0 >> C;
	y = REV( ( s[ p ] = s0 ^ s1 ) * M ); 
}

static uint64_t x; // Just to compile
void next1() { x ^= x >> A; x ^= x << B; x ^= x >> C; y = REV( x * M ); } // X3
void next2() { x ^= x << C; x ^= x >> B; x ^= x << A; y = REV( x * M ); } // X2
void next3() { x ^= x >> C; x ^= x << B; x ^= x >> A; y = REV( x * M ); } // X4
void next4() { x ^= x << A; x ^= x << C; x ^= x >> B; y = REV( x * M ); } // X5
void next5() { x ^= x >> A; x ^= x >> C; x ^= x << B; y = REV( x * M ); } // X6
void next6() { x ^= x >> B; x ^= x << A; x ^= x << C; y = REV( x * M ); } // X7
void next7() { x ^= x << B; x ^= x >> A; x ^= x >> C; y = REV( x * M ); } // X8

/* True if the lower part of y has already been returned. */
static int lower;
static void (*next)();

/* Note that this function returns a 32-bit number. */
unsigned long xorshift( void *unused0, void *unused1 ) {
	if ( lower ^= 1 ) return (uint32_t)y;
	const uint32_t result = y >> 32;
	next();
	return result;
}

#define NORM_64 ( ( 1./4 ) / ( 1LL << 62 ) )

double xorshift01( void *unused0, void *unused1 ) {
	if ( lower ) next(); // Refresh x (lower part has already been used).
	const double result = y * NORM_64;
	next();
	lower = 0;
	return result;
}

void write_state( void *unused ) {
	for( int i = 0; i < 16; i++ ) printf( "%s%llu", i ? " " : "", (unsigned long long)s[ i ] );
	printf("\n");
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


int main(int argc, char *argv[] ) {
	if ( argc != 7 ) {
		fprintf(stderr, "%s ALGORITHM A B C NUMBER WINDOW\n", argv[0] );
		exit(1);
	}

	switch( atoi(argv[1]) ) {
		case 0: next = next0; break;
		case 1: next = next1; break;
		case 2: next = next2; break;
		case 3: next = next3; break;
		case 4: next = next4; break;
		case 5: next = next5; break;
		case 6: next = next6; break;
		case 7: next = next7; break;
	}

	assert( next == next0 );

	A = atoi( argv[2] );
	B = atoi( argv[3] );
	C = atoi( argv[4] );

	const int n = atoi( argv[5] );
	const int k = atoi( argv[6] );
	unsigned long long c[ n + k ];
	memset( c, 0, sizeof c );
	
	for( int b = 0; b < 4096; b++ ) {
		memset( s, 0, sizeof s );
		s[ b / 64 ] = 1ULL << b % 64;
	
		for( int i = 0; i < n; i++ ) {	
			next();
			const int t = __builtin_popcountll( y );
			for( int j = 0; j < k; j++ ) c[ i + j ] += t;
		}
	}

	double norm = 1. / ( 4096 * k * 64 );
	for( int i = k; i < n; i++ ) printf( "%f\n", c[ i ] * norm );
}
