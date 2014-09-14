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

uint64_t u;
uint64_t v = 4101842887655102017LL;
uint64_t w = 1;

uint64_t next(void) {
	u = u * 2862933555777941757LL + 7046029254386353087LL;
	v ^= v >> 17;
	v ^= v << 31;
	v ^= v >> 8;
	w = 4294957665U * (w & 0xffffffff) + (w >> 32);
	uint64_t x = u ^ (u << 21);
	x ^= x >> 35;
	x ^= x << 4;
	return (x + v) ^ w;
}

void init( uint64_t j ) {
	// Call with any integer seed (except value of v above).
	u = j ^ v;
	if ( u == 0 ) abort();
	next();
	v = u;
	next();
	w = v;
	next();
}

uint64_t getusertime() {
	struct rusage rusage;
	getrusage( 0, &rusage );
	return rusage.ru_utime.tv_sec * 1000000ULL + ( rusage.ru_utime.tv_usec / 1000 ) * 1000;
}

int main( int argc, char* argv[] ) {
	long long int n = strtoll( argv[1], NULL, 0 );
	uint64_t x = 0;
	
	init( -1ULL / 3 );
	
	int64_t start = getusertime();
	for( long long int i = n; i-- != 0; ) x ^= next();
	int64_t elapsed = getusertime() - start;
	const double s = elapsed / 1E6;
	if ( x == 0 ) putchar(0);
	printf( "%f s, %.02f queries/s, %.02f ns/query\n", s, n / s, 1E9 * s / n );
	return 0;
}
