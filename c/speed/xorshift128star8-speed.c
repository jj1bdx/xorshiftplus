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

#include <stdint.h>

/* The current state of the generator. */
static uint64_t s[ 2 ] = { 1, 1 };

// Composed with M_8.
const int64_t M = 1181783497276652981LL;

static uint64_t __inline next(void) { 
	uint64_t s1 = s[ 0 ];
	const uint64_t s0 = s[ 1 ];
	s[ 0 ] = s0;
	s1 ^= s1 << 49;
	return ( s[ 1 ] = ( s1 ^ s0 ^ ( s1 >> 5 ) ^ ( s0 >> 26 ) ) ) * M;
}

#include "harness.c"
