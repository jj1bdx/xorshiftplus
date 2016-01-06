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

static const int64_t multiplier = 0x5DEECE66DL;
static const int64_t addend = 0xBL;
static const int64_t mask = (1LL << 48) - 1;

int64_t x = 1;

static __inline unsigned long next() {
	x = (x * multiplier + addend) & mask;
	return (uint32_t)(x >> 16);
}

#define NEXT next() ^ next()

#include "harness.c"
