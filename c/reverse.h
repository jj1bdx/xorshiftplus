#include <stdint.h>

#ifdef REVERSE
#define REVERSE_INFIX "-rev"

static __inline uint64_t reverse( uint64_t x ) {
	x = ((x >> 1) & 0x5555555555555555ULL) | ((x & 0x5555555555555555ULL) << 1);
	x = ((x >> 2) & 0x3333333333333333ULL) | ((x & 0x3333333333333333ULL) << 2);
	x = ((x >> 4) & 0x0F0F0F0F0F0F0F0FULL) | ((x & 0x0F0F0F0F0F0F0F0FULL) << 4);
	x = ((x >> 8) & 0x00FF00FF00FF00FFULL) | ((x & 0x00FF00FF00FF00FFULL) << 8);
	x = ((x >> 16) & 0x0000FFFF0000FFFFULL ) | ((x & 0x0000FFFF0000FFFFULL) << 16);
	return ( x >> 32 ) | ( x << 32 );
}

#define REV(x) (reverse(x))
#else
#define REVERSE_INFIX ""
#define REV(x) (x)
#endif
