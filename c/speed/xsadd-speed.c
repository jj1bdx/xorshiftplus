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

#define R (4)

uint32_t state[R] = { 1, 1, 1, 1 };

static __inline unsigned long next() {
	static const int sh1 = 15;
	static const int sh2 = 18;
	static const int sh3 = 11;
	uint32_t t;
	t = state[0];
	t ^= t << sh1;
	t ^= t >> sh2;
	t ^= state[3] << sh3;
	state[0] = state[1];
	state[1] = state[2];
	state[2] = state[3];
	state[3] = t;
	return state[3] + state[2];
}

#define NEXT next() ^ next()

#include "harness.c"
