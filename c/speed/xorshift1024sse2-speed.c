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

#include <stdint.h>
#include <emmintrin.h>

typedef union {
	__m128i m[ 8 ];
	uint64_t l[ 16 ];
} state_t;

/* The current state of the generator. */
static state_t s = { .l = { 1 } };

const int64_t M = 2685821657736338717LL;

static uint64_t __inline next(void) { 
	static int p = 0;
	if ( p++ == 16 ) {
		__m128i s0 = s.m[ 0 ];
		__m128i s1 = s.m[ 1 ];
		s1 = _mm_xor_si128( s1 , _mm_slli_si128( s1, 16 ) );
		s.m[ 0 ] = _mm_xor_si128( _mm_xor_si128( s0, s1 ), _mm_xor_si128( _mm_srli_si128( s1, 23 ), _mm_srli_si128( s0, 39 ) ) );

		s0 = s.m[ 1 ];
		s1 = s.m[ 2 ];
		s1 = _mm_xor_si128( s1 , _mm_slli_si128( s1, 16 ) );
		s.m[ 1 ] = _mm_xor_si128( _mm_xor_si128( s0, s1 ), _mm_xor_si128( _mm_srli_si128( s1, 23 ), _mm_srli_si128( s0, 39 ) ) );

		s0 = s.m[ 2 ];
		s1 = s.m[ 3 ];
		s1 = _mm_xor_si128( s1 , _mm_slli_si128( s1, 16 ) );
		s.m[ 2 ] = _mm_xor_si128( _mm_xor_si128( s0, s1 ), _mm_xor_si128( _mm_srli_si128( s1, 23 ), _mm_srli_si128( s0, 39 ) ) );

		s0 = s.m[ 3 ];
		s1 = s.m[ 4 ];
		s1 = _mm_xor_si128( s1 , _mm_slli_si128( s1, 16 ) );
		s.m[ 3 ] = _mm_xor_si128( _mm_xor_si128( s0, s1 ), _mm_xor_si128( _mm_srli_si128( s1, 23 ), _mm_srli_si128( s0, 39 ) ) );

		s0 = s.m[ 4 ];
		s1 = s.m[ 5 ];
		s1 = _mm_xor_si128( s1 , _mm_slli_si128( s1, 16 ) );
		s.m[ 4 ] = _mm_xor_si128( _mm_xor_si128( s0, s1 ), _mm_xor_si128( _mm_srli_si128( s1, 23 ), _mm_srli_si128( s0, 39 ) ) );

		s0 = s.m[ 5 ];
		s1 = s.m[ 6 ];
		s1 = _mm_xor_si128( s1 , _mm_slli_si128( s1, 16 ) );
		s.m[ 5 ] = _mm_xor_si128( _mm_xor_si128( s0, s1 ), _mm_xor_si128( _mm_srli_si128( s1, 23 ), _mm_srli_si128( s0, 39 ) ) );

		s0 = s.m[ 6 ];
		s1 = s.m[ 7 ];
		s1 = _mm_xor_si128( s1 , _mm_slli_si128( s1, 16 ) );
		s.m[ 6 ] = _mm_xor_si128( _mm_xor_si128( s0, s1 ), _mm_xor_si128( _mm_srli_si128( s1, 23 ), _mm_srli_si128( s0, 39 ) ) );

		s0 = s.m[ 7 ];
		s1 = s.m[ 0 ];
		s1 = _mm_xor_si128( s1 , _mm_slli_si128( s1, 16 ) );
		s.m[ 7 ] = _mm_xor_si128( _mm_xor_si128( s0, s1 ), _mm_xor_si128( _mm_srli_si128( s1, 23 ), _mm_srli_si128( s0, 39 ) ) );

		p = 0;
	}
	
	return s.l[ p ] * M;
}

#define INIT for(int i = 0; i < 16; i++) s.l[i] = 1;

#include "harness.c"
