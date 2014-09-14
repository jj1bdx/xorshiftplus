/* ***************************************************************************** */
/* Copyright:      Francois Panneton and Pierre L'Ecuyer, University of Montreal */
/*                 Makoto Matsumoto, Hiroshima University                        */
/* Notice:         This code can be used freely for personal, academic,          */
/*                 or non-commercial purposes. For commercial purposes,          */
/*                 please contact P. L'Ecuyer at: lecuyer@iro.UMontreal.ca       */
/* ***************************************************************************** */

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

#define W 32
#define R 32
#define M1 3
#define M2 24
#define M3 10

#define MAT0POS(t,v) (v^(v>>t))
#define MAT0NEG(t,v) (v^(v<<(-(t))))
#define Identity(v) (v)

#define V0            STATE[state_i                   ]
#define VM1           STATE[(state_i+M1) & 0x0000001fU]
#define VM2           STATE[(state_i+M2) & 0x0000001fU]
#define VM3           STATE[(state_i+M3) & 0x0000001fU]
#define VRm1          STATE[(state_i+31) & 0x0000001fU]
#define newV0         STATE[(state_i+31) & 0x0000001fU]
#define newV1         STATE[state_i                   ]

#define FACT 2.32830643653869628906e-10

static unsigned int state_i = 0;
static unsigned int STATE[R];
static unsigned int z0, z1, z2;

void init(unsigned int *init){
   int j;
   state_i = 0;
   for (j = 0; j < R; j++)
     STATE[j] = init[j];
}

#ifdef REVERSE

static __inline uint32_t reverse( uint32_t x ) {
	x = ((x >> 1) & 0x55555555U) | ((x & 0x55555555U) << 1);
	x = ((x >> 2) & 0x33333333U) | ((x & 0x33333333U) << 2);
	x = ((x >> 4) & 0x0F0F0F0FU) | ((x & 0x0F0F0F0FU) << 4);
	x = ((x >> 8) & 0x00FF00FFU) | ((x & 0x00FF00FFU) << 8);
	return ( x >> 16) | (x << 16 );
}

#define NAME "well1024a-rev"
#define REV(x) (reverse(x))
#else
#define NAME "well1024a"
#define REV(x) (x)
#endif

static unsigned long int next( void *unused0, void *unused1 ) {
  z0    = VRm1;
  z1    = Identity(V0)       ^ MAT0POS (8, VM1);
  z2    = MAT0NEG (-19, VM2) ^ MAT0NEG(-14,VM3);
  newV1 = z1                 ^ z2; 
  newV0 = MAT0NEG (-11,z0)   ^ MAT0NEG(-7,z1)    ^ MAT0NEG(-13,z2) ;
  state_i = (state_i + 31) & 0x0000001fU;
  return REV( STATE[state_i] );
}

#ifdef TESTU01
static double next01( void *unused0, void *unused1 ) {
	return ( (uint64_t)next(NULL, NULL) << 32 | (uint64_t)next(NULL, NULL) ) * ( 1 / ( 4. * ( 1ULL << 62 ) ) );
}
#endif

void write_state( void *unused ) {
	printf( " " );
	for( int i = 0; i < R; i++ ) printf( "0x%x ", STATE[i] );
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
	
	unsigned int seed[ R ];
	for( int i = 0; i < R; i++ ) seed[i] = strtoui_check( argv[i+1] );
	init(seed);

#ifdef TESTU01
	unif01_Gen well1024a;
	well1024a.name = NAME;
	well1024a.Write = write_state;
	well1024a.GetBits = next;
	well1024a.GetU01 = next01;
	TESTU01( &well1024a );
#else
	int x;
	for(;;) {
		x = next(NULL,NULL);
		fwrite( &x, 4, 1, stdout );
	}
#endif
	return 0;
}
