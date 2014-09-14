/**
 * @author Mutsuo Saito (Manieth Corp.)
 * @author Makoto Matsumoto (Hiroshima University)
 *
 * Copyright (c) 2014
 * Mutsuo Saito, Makoto Matsumoto, Hiroshima University
 * and Manieth Corp.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <inttypes.h>

#ifdef TESTU01
#include <unif01.h>
#include <bbattery.h>
#endif

#ifdef REVERSE

static __inline uint32_t reverse( uint32_t x ) {
	x = ((x >> 1) & 0x55555555U) | ((x & 0x55555555U) << 1);
	x = ((x >> 2) & 0x33333333U) | ((x & 0x33333333U) << 2);
	x = ((x >> 4) & 0x0F0F0F0FU) | ((x & 0x0F0F0F0FU) << 4);
	x = ((x >> 8) & 0x00FF00FFU) | ((x & 0x00FF00FFU) << 8);
	return ( x >> 16) | (x << 16 );
}

#define NAME "xsadd-rev"
#define REV(x) (reverse(x))
#else
#define NAME "xsadd"
#define REV(x) (x)
#endif

#define R (4)

uint32_t state[R];

static unsigned long int next( void *unused0, void *unused1 ) {
	static const int sh1 = 15;
	static const int sh2 = 18;
	static const int sh3 = 11;
	uint32_t t;
	t = state[0];
	t ^= t << sh1;
	t ^= t >> sh2;
	t ^= state[3] << sh3;
	state[0] = state[1];
	state[1] = state[2];
	state[2] = state[3];
	state[3] = t;
	return REV( state[3] + state[2] );
}

#ifdef TESTU01
static double next01( void *unused0, void *unused1 ) {
	return ( (uint64_t)next(NULL, NULL) << 32 | (uint64_t)next(NULL, NULL) ) * ( 1 / ( 4. * ( 1ULL << 62 ) ) );
}
#endif

void write_state( void *unused ) {
	printf( " " );
	for( int i = 0; i < R; i++ ) printf( "0x%x ", state[i] );
	printf( "\n" );
}

uint32_t strtoui_check( char *p ) {
	const uintmax_t result = strtoumax( p, NULL, 0 );
	if ( errno != 0 ) {
		fprintf(stderr, "Error while parsing seed: %s\n", strerror( errno ) );
		exit( 1 );
	}
	if ( result >= 1ULL << 32 ) {
		fprintf(stderr, "Seed must made of 32-bit values\n" );
		exit( 1 );
	}

	return result;
}


int main(int argc, char *argv[] ) {
	if ( argc != R + 1 ) {
		fprintf(stderr, "%s SEED (%d 32-bit integers)\n", argv[0], R );
		exit(1);
	}
	
	for( int i = 0; i < R; i++ ) state[i] = strtoui_check( argv[i+1] );

#ifdef TESTU01
	unif01_Gen xsadd;
	xsadd.name = NAME;
	xsadd.Write = write_state;
	xsadd.GetBits = next;
	xsadd.GetU01 = next01;
	TESTU01( &xsadd );
#else
	int x;
	for(;;) {
		x = next(NULL,NULL);
		fwrite( &x, 4, 1, stdout );
	}
#endif
	return 0;
}
