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
#include <string.h>

/* The internal state of the generator. */
static uint64_t x = 0x1LL;

/* The current 64-bit value output by the generator (this is not x if STAR32/STAR8/STAR2 is defined.) */
static uint64_t y;

/* The three shifts. */
static int A, B, C;

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

#if defined(STAR32) || defined(STAR8) || defined(STAR2)

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

void next0() { x ^= x << A; x ^= x >> B; x ^= x << C; y = x * M; } // X1
void next1() { x ^= x >> A; x ^= x << B; x ^= x >> C; y = x * M; } // X3
void next2() { x ^= x << C; x ^= x >> B; x ^= x << A; y = x * M; } // X2
void next3() { x ^= x >> C; x ^= x << B; x ^= x >> A; y = x * M; } // X4
void next4() { x ^= x << A; x ^= x << C; x ^= x >> B; y = x * M; } // X5
void next5() { x ^= x >> A; x ^= x >> C; x ^= x << B; y = x * M; } // X6
void next6() { x ^= x >> B; x ^= x << A; x ^= x << C; y = x * M; } // X7
void next7() { x ^= x << B; x ^= x >> A; x ^= x >> C; y = x * M; } // X8
#else

void next0() { x ^= x << A; x ^= x >> B; x ^= x << C; y = x; }
void next1() { x ^= x >> A; x ^= x << B; x ^= x >> C; y = x; }
void next2() { x ^= x << C; x ^= x >> B; x ^= x << A; y = x; }
void next3() { x ^= x >> C; x ^= x << B; x ^= x >> A; y = x; }
void next4() { x ^= x << A; x ^= x << C; x ^= x >> B; y = x; }
void next5() { x ^= x >> A; x ^= x >> C; x ^= x << B; y = x; }
void next6() { x ^= x >> B; x ^= x << A; x ^= x << C; y = x; }
void next7() { x ^= x << B; x ^= x >> A; x ^= x >> C; y = x; }

#endif

/* True if the lower part of y has already been returned. */
static int lower;
static void (*next)();

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

	A = atoi( argv[2] );
	B = atoi( argv[3] );
	C = atoi( argv[4] );

	const int n = atoi( argv[5] );
	const int k = atoi( argv[6] );
	unsigned long long c[ n + k ];
	memset( c, 0, sizeof c );
	
	for( int b = 0; b < 64; b++ ) {
		x = 1ULL << b;
	
		for( int i = 0; i < n; i++ ) {	
			next();
			const int t = __builtin_popcountll( y );
			for( int j = 0; j < k; j++ ) c[ i + j ] += t;
		}
	}

	double norm = 1. / ( 64 * k * 64 );
	for( int i = k; i < n; i++ ) printf( "%f\n", c[ i ] * norm );
}
