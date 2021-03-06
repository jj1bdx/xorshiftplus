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
static uint64_t s[16];

static uint64_t __inline next(void) { 
	static int p;
	const uint64_t s0 = s[ p ];
	uint64_t s1 = s[ p = ( p + 1 ) & 15 ];
	s1 ^= s1 << 31;
	return ( s[ p ] = ( s1 ^ s0 ^ ( s1 >> 11 ) ^ ( s0 >> 30 ) ) ) + s0; 
}

#define INIT for(int i = 0; i < 16; i++) s[i] = 1;

#include "harness.c"
