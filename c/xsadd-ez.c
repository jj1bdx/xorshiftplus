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

#define R (4)

uint32_t state[R];

static unsigned long int next() {
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
	return state[3] + state[2];
}

int main(int argc, char *argv[] ) {
	if ( argc != 3 ) {
		fprintf(stderr, "%s NUMBER WINDOW\n", argv[0] );
		exit(1);
	}

	const int n = atoi( argv[1] );
	const int k = atoi( argv[2] );
	unsigned long long c[ n + k ];
	memset( c, 0, sizeof c );
	
	for( int b = 0; b < 128; b++ ) {
		memset( state, 0, sizeof state );
		state[ b / 32 ] = 1U << b % 32;
	
		for( int i = 0; i < n; i++ ) {	
			const uint64_t high = (uint64_t)next() << 32;
			const uint64_t low = (uint64_t)next();
			const int t = __builtin_popcountll( high | low );
			for( int j = 0; j < k; j++ ) c[ i + j ] += t;
		}
	}

	double norm = 1. / ( 128 * k * 64 );
	for( int i = k; i < n; i++ ) printf( "%f\n", c[ i ] * norm );
}
