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

/* The current state of the generator. */
static uint64_t s[64];

const int64_t M = 8372773778140471301LL;
				
static uint64_t next(void) { 
	static int p;
	uint64_t s0 = s[ p ];
	uint64_t s1 = s[ p = ( p + 1 ) & 63 ];
	s1 ^= s1 << 25;
	s1 ^= s1 >> 3;
	s0 ^= s0 >> 49;
	return ( s[ p ] = s0 ^ s1 ) * M; 
}

#define INIT for(int i = 0; i < 64; i++) s[i] = 1;

#include "harness.c"
