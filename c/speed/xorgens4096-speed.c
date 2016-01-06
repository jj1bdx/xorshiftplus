/* xorgens.c version 3.05, R. P. Brent, 20080920.

==========================================================================
|                                                                        |
|  Copyright (C) 2004, 2006, 2008 R. P. Brent.                           |
|                                                                        |
|  This program is free software; you can redistribute it and/or         |
|  modify it under the terms of the GNU General Public License,          |
|  version 2, June 1991, as published by the Free Software Foundation.   |
|  For details see http://www.gnu.org/copyleft/gpl.html .                |
|                                                                        |
|  If you would like to use this software but the GNU GPL creates legal  |
|  problems, then please contact the author to negotiate a special       |
|  agreement.                                                            |
|                                                                        |
==========================================================================

   For type definitions see xorgens.h */

#include <stdint.h>
#include "xorgens.h"

#define wlen 64
#define r    64
#define s    53
#define a    33
#define b    26
#define c    27
#define d    29
#define ws   27

#define weyl (((((UINT)0x61c88646)<<16)<<16) + (UINT)0x80b583eb)
static uint64_t w, x[r];

static __inline uint64_t next(void) {
	static int i = -1;
	uint64_t t, v;
	
	t = x[i = (i+1)&(r-1)];		/* Assumes that r is a power of two */
	v = x[(i+(r-s))&(r-1)];		/* Index is (i-s) mod r */
	t ^= t<<a;	t ^= t>>b;		/* (I + L^a)(I + R^b) */
	v ^= v<<c;	v ^= v>>d;		/* (I + L^c)(I + R^d) */
	x[i] = (v ^= t);				/* Update circular array */
	w += weyl;						/* Update Weyl generator */
	return (v + (w^(w>>ws)));	/* Return combination */
}

#define INIT for(int i = 0; i < r; i++) x[i] = 1;

#include "harness.c"
