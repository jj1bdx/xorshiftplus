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

static const int64_t multiplier = 0x5DEECE66DL;
static const int64_t addend = 0xBL;
static const int64_t mask = (1LL << 48) - 1;

int64_t x;

void setseed( uint64_t s ) {
	x = (s ^ multiplier) & mask;
}

static __inline unsigned long jnext() {
	x = (x * multiplier + addend) & mask;
	return (uint32_t)(x >> 16);
}

uint64_t getusertime() {
	struct rusage rusage;
	getrusage( 0, &rusage );
	return rusage.ru_utime.tv_sec * 1000000ULL + ( rusage.ru_utime.tv_usec / 1000 ) * 1000;
}

int main( int argc, char* argv[] ) {
	long long int n = strtoll( argv[1], NULL, 0 );
	uint64_t x = 0;
	
	setseed(0);
	
	int64_t start = getusertime();
	for( long long int i = n; i-- != 0; ) {
		x ^= jnext();
		x ^= jnext();
	}
	int64_t elapsed = getusertime() - start;
	const double s = elapsed / 1E6;
	if ( x == 0 ) putchar(0);
	printf( "%f s, %.02f queries/s, %.02f ns/query\n", s, n / s, 1E9 * s / n );
	return 0;
}
