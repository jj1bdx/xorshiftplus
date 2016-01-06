for i in *-speed.c; do clang -O3 -std=c99 -DHAVE_SSE2 -msse4.2 $i -o ${i%.c}-clang; done
for i in *-speed.c; do gcc -O3 -std=c99 -DHAVE_SSE2 -msse4.2 $i -o ${i%.c}-gcc; done
for i in *-speed.c; do gcc -O3 -fno-move-loop-invariants -fno-unroll-loops -std=c99 -DHAVE_SSE2 -msse4.2 $i -o ${i%.c}-gcc-nl; done
