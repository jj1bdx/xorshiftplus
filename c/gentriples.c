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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

/* We compute the triple giving full-period Xorshift generators, and perform some additional checks. */

/* Representation of a 64x64 matrix over Z/2. */
typedef struct {
	uint64_t row[64];
} matrix;

/* 2^64-1, divided by each of its prime factors. */
uint64_t fact[] = { -1ULL / 6700417, -1ULL / 65537, -1ULL / 641, -1ULL / 257, -1ULL / 17, -1ULL / 5, -1ULL / 3 }; 

/* The valid triples. */
int triple[275][3] = { {1,1,54}, {1,1,55}, {1,3,45}, {1,7,9}, {1,7,44}, {1,7,46}, {1,9,50}, {1,11,35}, {1,11,50},
{1,13,45}, {1,15,4}, {1,15,63}, {1,19,6}, {1,19,16}, {1,23,14}, {1,23,29}, {1,29,34}, {1,35,5}, {1,35,11}, {1,35,34},
{1,45,37}, {1,51,13}, {1,53,3}, {1,59,14}, {2,13,23}, {2,31,51}, {2,31,53}, {2,43,27}, {2,47,49}, {3,1,11}, {3,5,21},
{3,13,59}, {3,21,31}, {3,25,20}, {3,25,31}, {3,25,56}, {3,29,40}, {3,29,47}, {3,29,49}, {3,35,14}, {3,37,17}, {3,43,4},
{3,43,6}, {3,43,11}, {3,51,16}, {3,53,7}, {3,61,17}, {3,61,26}, {4,7,19}, {4,9,13}, {4,15,51}, {4,15,53}, {4,29,45},
{4,29,49}, {4,31,33}, {4,35,15}, {4,35,21}, {4,37,11}, {4,37,21}, {4,41,19}, {4,41,45}, {4,43,21}, {4,43,31}, {4,53,7},
{5,9,23}, {5,11,54}, {5,15,27}, {5,17,11}, {5,23,36}, {5,33,29}, {5,41,20}, {5,45,16}, {5,47,23}, {5,53,20}, {5,59,33},
{5,59,35}, {5,59,63}, {6,1,17}, {6,3,49}, {6,17,47}, {6,23,27}, {6,27,7}, {6,43,21}, {6,49,29}, {6,55,17}, {7,5,41},
{7,5,47}, {7,5,55}, {7,7,20}, {7,9,38}, {7,11,10}, {7,11,35}, {7,13,58}, {7,19,17}, {7,19,54}, {7,23,8}, {7,25,58},
{7,27,59}, {7,33,8}, {7,41,40}, {7,43,28}, {7,51,24}, {7,57,12}, {8,5,59}, {8,9,25}, {8,13,25}, {8,13,61}, {8,15,21},
{8,25,59}, {8,29,19}, {8,31,17}, {8,37,21}, {8,51,21}, {9,1,27}, {9,5,36}, {9,5,43}, {9,7,18}, {9,19,18}, {9,21,11},
{9,21,20}, {9,21,40}, {9,23,57}, {9,27,10}, {9,29,12}, {9,29,37}, {9,37,31}, {9,41,45}, {10,7,33}, {10,27,59},
{10,53,13}, {11,5,32}, {11,5,34}, {11,5,43}, {11,5,45}, {11,9,14}, {11,9,34}, {11,13,40}, {11,15,37}, {11,23,42},
{11,23,56}, {11,25,48}, {11,27,26}, {11,29,14}, {11,31,18}, {11,53,23}, {12,1,31}, {12,3,13}, {12,3,49}, {12,7,13},
{12,11,47}, {12,25,27}, {12,39,49}, {12,43,19}, {13,3,40}, {13,3,53}, {13,7,17}, {13,9,15}, {13,9,50}, {13,13,19},
{13,17,43}, {13,19,28}, {13,19,47}, {13,21,18}, {13,21,49}, {13,29,35}, {13,35,30}, {13,35,38}, {13,47,23}, {13,51,21},
{14,13,17}, {14,15,19}, {14,23,33}, {14,31,45}, {14,47,15}, {15,1,19}, {15,5,37}, {15,13,28}, {15,13,52}, {15,17,27},
{15,19,63}, {15,21,46}, {15,23,23}, {15,45,17}, {15,47,16}, {15,49,26}, {16,5,17}, {16,7,39}, {16,11,19}, {16,11,27},
{16,13,55}, {16,21,35}, {16,25,43}, {16,27,53}, {16,47,17}, {17,15,58}, {17,23,29}, {17,23,51}, {17,23,52}, {17,27,22},
{17,45,22}, {17,47,28}, {17,47,29}, {17,47,54}, {18,1,25}, {18,3,43}, {18,19,19}, {18,25,21}, {18,41,23}, {19,7,36},
{19,7,55}, {19,13,37}, {19,15,46}, {19,21,52}, {19,25,20}, {19,41,21}, {19,43,27}, {20,1,31}, {20,5,29}, {21,1,27},
{21,9,29}, {21,13,52}, {21,15,28}, {21,15,29}, {21,17,24}, {21,17,30}, {21,17,48}, {21,21,32}, {21,21,34}, {21,21,37},
{21,21,38}, {21,21,40}, {21,21,41}, {21,21,43}, {21,41,23}, {22,3,39}, {23,9,38}, {23,9,48}, {23,9,57}, {23,13,38},
{23,13,58}, {23,13,61}, {23,17,25}, {23,17,54}, {23,17,56}, {23,17,62}, {23,41,34}, {23,41,51}, {24,9,35}, {24,11,29},
{24,25,25}, {24,31,35}, {25,7,46}, {25,7,49}, {25,9,39}, {25,11,57}, {25,13,29}, {25,13,39}, {25,13,62}, {25,15,47},
{25,21,44}, {25,27,27}, {25,27,53}, {25,33,36}, {25,39,54}, {28,9,55}, {28,11,53}, {29,27,37}, {31,1,51}, {31,25,37},
{31,27,35}, {33,31,43}, {33,31,55}, {43,21,46}, {49,15,61}, {55,9,56} };

/* Here we store the 2200 matrice with full period. */
matrix M[2200];

int matrix_cmp( const void *a, const void *b ) {
	return memcmp( a, b, sizeof(matrix) );
}

bool is_identity( matrix *m ) {
	for( int i = 0; i < 64; i++ ) if ( m->row[i] != ( 1ULL << i ) ) return false;
	return true;
}

bool is_equal( matrix *x, matrix *y ) {
	for( int i = 0; i < 64; i++ ) if ( x->row[i] != y->row[i] ) return false;
	return true;
}

/* x <- xy */
void mult( matrix *x, matrix *y ) {
	matrix u;
	for( int i = 64; i-- != 0; ) {
		const uint64_t rx = x->row[i];
		uint64_t ra = 0;
		for( int j = 64; j-- != 0; ) if ( rx & 1ULL << j ) ra ^= y->row[j];
		u.row[i] = ra;
	}
	
	*x = u;
}

void print_matrix( matrix *x ) {
	for( int i = 0; i < 64; i++ ) {
		const uint64_t rx = x->row[i];
		for( int j = 0; j < 64; j++ ) printf( "%d", ( rx & 1ULL << j ) != 0 );
		printf( "\n" );
	}
}

/* x <- I */
void identity( matrix *x ) {
	for( int i = 64; i-- != 0; ) x->row[i] = 1ULL << i;
}

/* q <- { x^(2^0), x^(2^1), ..., x^(2^63) } */
void quad( matrix *q, matrix *x ) {
	q[0] = *x;
	for( int i = 1; i < 64; i++ )	{
		q[i] = q[i-1];
		mult( &q[i], &q[i] );
	}
}

/* Assuming q = quad(y), x <- y^p. */
void mpow( matrix *x, matrix *q, uint64_t p ) {
	identity( x );
	for( int i = 64; i-- != 0; ) 
		if ( p & 1ULL << i ) mult( x, &q[i] );
}

bool is_full( matrix *x ) {
	matrix q[64];
	quad( q, x );
	matrix p;
	mpow( &p, q, -1ULL ); // p = q^{2^64-1}
	if ( is_identity( &p ) ) {
		int i;
		// Check each factor
		for( i = sizeof fact / sizeof *fact; i-- != 0; ) {
			mpow( &p, q, fact[i] );
			if ( is_identity( &p ) ) break;
		}
		if ( i == -1 ) return true;
	}

	return false;
}

int main( int argc, char * argv[] ) {
	
	matrix r[64], l[64], id;
	// Compute basic matrices: identity, (I+L^x), (I+R^x).
	identity( &id );
	for( int i = 0; i < 63; i++ ) r[1].row[i+1] |= 1ULL << i;
	for( int i = 0; i < 63; i++ ) l[1].row[i] |= 1ULL << (i + 1);
	for( int i = 2; i < 64; i++ ) {
		l[i] = l[i-1];
		r[i] = r[i-1];
		mult( &l[i], &l[1] );
		mult( &r[i], &r[1] );
	}
	for( int i = 64; i-- != 0; )
		for( int j = 64; j-- != 0; ) {
			r[i].row[j] |= 1ULL << j;
			l[i].row[j] |= 1ULL << j;
		}

#ifdef TRIPLES
	/* Search for triples giving full period with algorithm A_0. We only
	   care for triples <a,b,c> with c >= a as we will get the same
	   transformation by A_2 anyway. */
	int t = 0;
	for( int a = 1; a < 64; a++ ) {
		for( int b = 1; b < 64; b++ ) {
			for( int c = a; c < 64; c++ ) {
				// A0
				matrix x = l[a];
				mult( &x, &r[b] );
				mult( &x, &l[c] );

				if ( is_full( &x ) ) {
					assert( t < sizeof triple/ sizeof *triple );
					assert( triple[ t ][ 0 ] == a );
					assert( triple[ t ][ 1 ] == b );
					assert( triple[ t ][ 2 ] == c );
					t++;
					printf( "%d %d %d\n", a, b, c );
				}
			}
		}
	}	

	assert( t == sizeof triple/ sizeof *triple );
#endif

	/* Check that we have full period with all eight algorithms. */
	int m = 0;

	for( int i = 0; i < sizeof triple/ sizeof *triple; i++ ) {
		int a = triple[i][0], b = triple[i][1], c = triple[i][2]; 
		matrix x;
		// A0
		x = l[a];
		mult( &x, &r[b] );
		mult( &x, &l[c] );
		M[ m++ ] = x;
		assert( is_full( &x ) );
		// A1	
		x = r[a];
		mult( &x, &l[b] );
		mult( &x, &r[c] );
		M[ m++ ] = x;
		assert( is_full( &x ) );
		// A2	
		x = l[c];
		mult( &x, &r[b] );
		mult( &x, &l[a] );
		M[ m++ ] = x;
		assert( is_full( &x ) );
		// A3	
		x = r[c];
		mult( &x, &l[b] );
		mult( &x, &r[a] );
		M[ m++ ] = x;
		assert( is_full( &x ) );
		// A4	
		x = l[a];
		mult( &x, &l[c] );
		mult( &x, &r[b] );
		M[ m++ ] = x;
		assert( is_full( &x ) );
		// A5	
		x = r[a];
		mult( &x, &r[c] );
		mult( &x, &l[b] );
		M[ m++ ] = x;
		assert( is_full( &x ) );
		// A6
		x = r[b];
		mult( &x, &l[a] );
		mult( &x, &l[c] );
		M[ m++ ] = x;
		assert( is_full( &x ) );
		// A7	
		x = l[b];
		mult( &x, &r[a] );
		mult( &x, &r[c] );
		M[ m++ ] = x;
		assert( is_full( &x ) );
	}
	
	assert( m == 2200 );

	/* Check that no two algorithms are the same. */
	qsort( M, m, sizeof *M, matrix_cmp );
	for( int i = m - 1; i-- != 0; ) assert( ! is_equal( &M[i], &M[i+1] ) );

	return 0;
}
