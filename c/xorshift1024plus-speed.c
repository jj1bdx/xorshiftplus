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
#include <sys/time.h>
#include <sys/resource.h>

/* The current state of the generator. */
static uint64_t s[ 16 ];

static uint64_t __inline next(void) { 
	static int p;
	const uint64_t s0 = s[ p ];
	uint64_t s1 = s[ p = ( p + 1 ) & 15 ];
	s1 ^= s1 << 31;
	return ( s[ p ] = ( s1 ^ s0 ^ ( s1 >> 11 ) ^ ( s0 >> 30 ) ) ) + s0; 
}

uint64_t getusertime() {
	struct rusage rusage;
	getrusage( 0, &rusage );
	return rusage.ru_utime.tv_sec * 1000000ULL + ( rusage.ru_utime.tv_usec / 1000 ) * 1000;
}

int main( int argc, char* argv[] ) {
	const long long int n = strtoll( argv[1], NULL, 0 );
	uint64_t t = 0;

	for( int i = 0; i < 16; i++ ) s[ i ] = -1ULL / 3;

	const int64_t start = getusertime();

	for( long long int i = n; i-- != 0; ) t ^= next();

	const int64_t elapsed = getusertime() - start;
	const double secs = elapsed / 1E6;
	printf( "%f s, %.02f queries/s, %.02f ns/query\n", secs, n / secs, 1E9 * secs / n );
	if ( t == 0 ) putchar( 0 );
	return 0;
}
