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
#include <inttypes.h>

#ifdef TESTU01
#include <unif01.h>
#include <bbattery.h>
#endif

#include "reverse.h"

#define NN 312
#define MM 156
#define MATRIX_A 0xB5026F5AA96619E9ULL
#define UM 0xFFFFFFFF80000000ULL /* Most significant 33 bits */
#define LM 0x7FFFFFFFULL /* Least significant 31 bits */


/* The array for the state vector */
static unsigned long long mt[NN]; 
/* mti==NN+1 means mt[NN] is not initialized */
static int mti=NN+1; 

/* initializes mt[NN] with a seed */
void init_genrand64(unsigned long long seed)
{
    mt[0] = seed;
    for (mti=1; mti<NN; mti++) 
        mt[mti] =  (6364136223846793005ULL * (mt[mti-1] ^ (mt[mti-1] >> 62)) + mti);
}

/* generates a random number on [0, 2^64-1]-interval */
unsigned long long mt19937_64(void)
{
    int i;
    unsigned long long x;
    static unsigned long long mag01[2]={0ULL, MATRIX_A};

    if (mti >= NN) { /* generate NN words at one time */
        for (i=0;i<NN-MM;i++) {
            x = (mt[i]&UM)|(mt[i+1]&LM);
            mt[i] = mt[i+MM] ^ (x>>1) ^ mag01[(int)(x&1ULL)];
        }
        for (;i<NN-1;i++) {
            x = (mt[i]&UM)|(mt[i+1]&LM);
            mt[i] = mt[i+(MM-NN)] ^ (x>>1) ^ mag01[(int)(x&1ULL)];
        }
        x = (mt[NN-1]&UM)|(mt[0]&LM);
        mt[NN-1] = mt[MM-1] ^ (x>>1) ^ mag01[(int)(x&1ULL)];

        mti = 0;
    }
  
  
    x = mt[mti++];

    x ^= (x >> 29) & 0x5555555555555555ULL;
    x ^= (x << 17) & 0x71D67FFFEDA60000ULL;
    x ^= (x << 37) & 0xFFF7EEE000000000ULL;
    x ^= (x >> 43);

    return x;
}

uint64_t strtoull_check( char *p ) {
	if ( p == NULL ) return 0;
	const uint64_t result = strtoull( p, NULL, 0 );
	if ( errno != 0 ) {
		fprintf(stderr, "Error while parsing seed: %s\n", strerror( errno ) );
		exit( 1 );
	}
	if ( 1 << 10 < result && result < 1ULL << 32 ) fprintf(stderr, "Suspiciosly 32-bit value while parsing seed: %llu\n", (unsigned long long)result );
	return result;
}

#define NORM_64 ( ( 1./4 ) / ( 1LL << 62 ) )

/* True if the lower part of y has already been returned. */
static int lower;

static uint64_t y;

void write_state( void *unused ) {
	printf( " " );
	for( int i = 0; i < NN; i++ ) printf( "0x%llx ", mt[i] );
	printf( "\n" );
}

/* Note that this function returns a 32-bit number. */
unsigned long mt19937( void *unused0, void *unused1 ) {
	if ( lower ^= 1 ) return (uint32_t)y;
	const uint32_t result = y >> 32;
	y = REV( mt19937_64() );
	return result;
}

double mt19937_01( void *unused0, void *unused1 ) {
	if ( lower ) y = REV( mt19937_64() ); // Refresh x (lower part has already been used).
	const double result = y * NORM_64;
	y = REV( mt19937_64() );
	lower = 0;
	return result;
}

int main(int argc, char *argv[]) {
	if ( argc != NN + 1 ) {
		fprintf(stderr, "%s SEED (%d 64-bit integers)\n", argv[0], NN );
		exit(1);
	}
	
	// Shift the seed, as it's 19968 = 19937+31 bits.
	for( int i = 0; i < NN; i++ ) mt[i] = strtoull_check( argv[i+1] ) << 31 | strtoull_check( argv[i+2] ) >> 33;

#ifdef TESTU01
	unif01_Gen gen;
	gen.name = "mt19937-64" REVERSE_INFIX;
	gen.Write = write_state;
	gen.GetBits = mt19937;
	gen.GetU01 = mt19937_01;
	TESTU01( &gen );
#else
	assert(freopen(NULL, "wb", stdout));

	for(;;) {
		const uint32_t z = mt19937( NULL, NULL );
		fwrite(&z, sizeof z, 1, stdout);
	}
#endif

	return 0;
}
