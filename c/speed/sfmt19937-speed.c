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

#define SFMT_MEXP (19937)

#include "SFMT.h"
#include "SFMT.c"

sfmt_t sfmt = { { { .u64 = { 1, 1 } } } };

#define INIT sfmt_init_gen_rand(&sfmt, -1);
#define NEXT sfmt_genrand_uint64(&sfmt)

#include "harness.c"
