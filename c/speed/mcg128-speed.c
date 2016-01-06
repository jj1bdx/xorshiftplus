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
static union {
	__int128_t x;
	uint64_t s[ 2 ];
} state = { .s = { 1, 1 } };

static uint64_t __inline next(void) { 
	state.x *= ( (__int128_t)0x12E15E35B500F16EULL << 64 | (__int128_t)0x2E714EB2B37916A5ULL );
	return state.s[ 1 ];
}

#include "harness.c"
