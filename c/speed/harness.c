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
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/resource.h>

#ifdef PAPI
#include <papi.h>
#endif

// This statement is executed, if necessary, to initialize the generator
#ifndef INIT
#define INIT
#endif

// We measure this function
#ifndef NEXT
#define NEXT next()
#endif

uint64_t get_user_time() {
	struct rusage rusage;
	getrusage( 0, &rusage );
	return rusage.ru_utime.tv_sec * 1000000000ULL + rusage.ru_utime.tv_usec * 1000ULL;;
}

int main( int argc, char* argv[] ) {
	if ( argc != 2 ) {
		fprintf( stderr, "USAGE: %s ITERATIONS\n", argv[ 0 ] );
		exit(1);
	}
	const long long int n = strtoll( argv[1], NULL, 0 );
	uint64_t e = -1;

	INIT // Here you can optionally inject initialization code

#ifdef PAPI

	const uint64_t start_cycle = PAPI_get_real_cyc();
	for( int64_t i = n; i-- != 0; ) e ^= NEXT; // Measurement
	const uint64_t cycles = ( PAPI_get_real_cyc() - start_cycle );

	printf( "%s: %" PRId64 " cycles, %.03f B/cycle,  %.03f cycles/B, %.03f words/cycle, %.03f cycles/word\n", argv[ 0 ], cycles, ( n * 8. ) / cycles, cycles / ( n * 8. ), n / (double)cycles, cycles / (double)n );

#else

	const uint64_t start_time = get_user_time();
	for( int64_t i = n; i-- != 0; ) e ^= NEXT; // Measurement
	const uint64_t t = ( get_user_time() - start_time );

	printf( "%s: %.03f s, %.03f GB/s, %.03f words/ns, %.03f ns/word\n", argv[ 0 ], t / 1E9, ( n * 8. ) / t, n / (double)t, t / (double)n );

#endif

	const volatile uint64_t unused = e;
	return 0;
}
