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

#ifdef TESTU01
#include <unif01.h>
#include <bbattery.h>
#endif

static const int64_t multiplier = 0x5DEECE66DL;
static const int64_t addend = 0xBL;
static const int64_t mask = (1LL << 48) - 1;

int64_t x;

#ifdef REVERSE

static __inline uint32_t reverse( uint32_t x ) {
	x = ((x >> 1) & 0x55555555U) | ((x & 0x55555555U) << 1);
	x = ((x >> 2) & 0x33333333U) | ((x & 0x33333333U) << 2);
	x = ((x >> 4) & 0x0F0F0F0FU) | ((x & 0x0F0F0F0FU) << 4);
	x = ((x >> 8) & 0x00FF00FFU) | ((x & 0x00FF00FFU) << 8);
	return ( x >> 16) | (x << 16 );
}

#define NAME "java-rev"
#define REV(x) (reverse(x))
#else
#define NAME "java"
#define REV(x) (x)
#endif


void setseed( uint64_t s ) {
	x = (s ^ multiplier) & mask;
}

unsigned long jnext( void *unused0, void *unused1 ) {
	x = (x * multiplier + addend) & mask;
	return REV( (uint32_t)(x >> 16) );
}

double jnext01( void *unused0, void *unused1 ) {
	return (((uint64_t)(jnext(NULL, NULL) >> 6) << 27) + ( jnext(NULL, NULL) >> 5) ) / (double)(1LL << 53);
}

void write_state( void *unused ) {
	printf ( " x = %llx\n", (unsigned long long)x );
}

uint64_t strtoull_check( char *p ) {
	const uint64_t result = strtoull( p, NULL, 0 );
	if ( errno != 0 ) {
		fprintf(stderr, "Error while parsing seed: %s\n", strerror( errno ) );
		exit( 1 );
	}
	if ( 1 << 10 < result && result < 1ULL << 32 ) fprintf(stderr, "Suspiciosly 32-bit value while parsing seed: %llu\n", (unsigned long long)result );
	if ( result > 1ULL << 48 ) {
		fprintf(stderr, "Seed must be a 48-bit value\n" );
		exit( 1 );
	}
	return result;
}


int main(int argc, char *argv[] ) {
	if (argc < 2) {
		fprintf(stderr, "%s SEED (a 48-bit integer)\n", argv[0] );
		exit(1);
	}

	setseed( strtoull_check( argv[1] ) );

#ifdef TESTU01
	unif01_Gen gen;
	gen.name = NAME;
	gen.Write = write_state;
	gen.GetBits = jnext;
	gen.GetU01 = jnext01;
	TESTU01( &gen );
#else
	assert(freopen(NULL, "wb", stdout));

	for(;;) {
		const uint32_t z = jnext( NULL, NULL );
		fwrite(&z, sizeof z, 1, stdout);
	}
#endif

	return 0;
}
