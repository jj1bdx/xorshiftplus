#!/bin/sh

CC=clang

${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_SmallCrush -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64-crush-small

${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_SmallCrush -DSTAR32 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star32-crush-small
${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_SmallCrush -DSTAR32 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star32-rev-crush-small
${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_SmallCrush -DSTAR8 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star8-crush-small
${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_SmallCrush -DSTAR8 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star8-rev-crush-small
${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_SmallCrush -DSTAR2 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star2-crush-small
${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_SmallCrush -DSTAR2 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star2-rev-crush-small

${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_SmallCrush -DADD -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128plus-crush-small
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_SmallCrush -DADD -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128plus-rev-crush-small

${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_Crush -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64-crush-medium

${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_Crush -DSTAR32 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star32-crush-medium
${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_Crush -DSTAR32 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star32-rev-crush-medium
${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_Crush -DSTAR8 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star8-crush-medium
${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_Crush -DSTAR8 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star8-rev-crush-medium
${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_Crush -DSTAR2 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star2-crush-medium
${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_Crush -DSTAR2 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star2-rev-crush-medium

${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_Crush -DADD -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128plus-crush-medium
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_Crush -DADD -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128plus-rev-crush-medium

${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64-crush-full

${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR32 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star32-crush-full
${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR32 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star32-rev-crush-full
${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR8 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star8-crush-full
${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR8 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star8-rev-crush-full
${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR2 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star2-crush-full
${CC} -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR2 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift64star2-rev-crush-full


${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_SmallCrush -DSTAR32 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star32-crush-small
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_SmallCrush -DSTAR32 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star32-rev-crush-small
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_SmallCrush -DSTAR8 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star8-crush-small
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_SmallCrush -DSTAR8 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star8-rev-crush-small
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_SmallCrush -DSTAR2 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star2-crush-small
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_SmallCrush -DSTAR2 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star2-rev-crush-small

${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_Crush -DSTAR32 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star32-crush-medium
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_Crush -DSTAR32 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star32-rev-crush-medium
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_Crush -DSTAR8 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star8-crush-medium
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_Crush -DSTAR8 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star8-rev-crush-medium
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_Crush -DSTAR2 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star2-crush-medium
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_Crush -DSTAR2 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star2-rev-crush-medium

${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128-crush-full

${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR32 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star32-crush-full
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR32 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star32-rev-crush-full
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR8 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star8-crush-full
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR8 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star8-rev-crush-full
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR2 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star2-crush-full
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR2 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128star2-rev-crush-full

${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DADD -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128plus-crush-full
${CC} -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DADD -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift128plus-rev-crush-full

${CC} -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift1024-crush-full
${CC} -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift1024-rev-crush-full

${CC} -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR32 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift1024star32-crush-full
${CC} -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR32 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift1024star32-rev-crush-full

${CC} -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR8 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift1024star8-crush-full
${CC} -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR8 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift1024star8-rev-crush-full

${CC} -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR2 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift1024star2-crush-full
${CC} -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR2 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift1024star2-rev-crush-full

${CC} -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DADD -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift1024plus-crush-full
${CC} -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DADD -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift1024plus-rev-crush-full

${CC} -std=c99 -Wall xorshift1024.c -O3 -DSTAR32 -o xorshift1024star32-stdout
${CC} -std=c99 -Wall xorshift1024.c -O3 -DSTAR32 -DREVERSE -o xorshift1024star32-rev-stdout

${CC} -std=c99 -Wall xorshift1024.c -O3 -DSTAR8 -o xorshift1024star8-stdout
${CC} -std=c99 -Wall xorshift1024.c -O3 -DSTAR8 -DREVERSE -o xorshift1024star8-rev-stdout

${CC} -std=c99 -Wall xorshift1024.c -O3 -DSTAR2 -o xorshift1024star2-stdout
${CC} -std=c99 -Wall xorshift1024.c -O3 -DSTAR2 -DREVERSE -o xorshift1024star2-rev-stdout


${CC} -std=c99 -Wall xorshift4096.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift4096-crush-full
${CC} -std=c99 -Wall xorshift4096.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift4096-rev-crush-full

${CC} -std=c99 -Wall xorshift4096.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR32 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift4096star32-crush-full
${CC} -std=c99 -Wall xorshift4096.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR32 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift4096star32-rev-crush-full

${CC} -std=c99 -Wall xorshift4096.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR8 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift4096star8-crush-full
${CC} -std=c99 -Wall xorshift4096.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR8 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift4096star8-rev-crush-full

${CC} -std=c99 -Wall xorshift4096.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR2 -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift4096star2-crush-full
${CC} -std=c99 -Wall xorshift4096.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DSTAR2 -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorshift4096star2-rev-crush-full

${CC} -std=c99 -Wall xorshift4096.c -O3 -DSTAR32 -o xorshift4096star32-stdout
${CC} -std=c99 -Wall xorshift4096.c -O3 -DSTAR32 -DREVERSE -o xorshift4096star32-rev-stdout

${CC} -std=c99 -Wall xorshift4096.c -O3 -DSTAR8 -o xorshift4096star8-stdout
${CC} -std=c99 -Wall xorshift4096.c -O3 -DSTAR8 -DREVERSE -o xorshift4096star8-rev-stdout

${CC} -std=c99 -Wall xorshift4096.c -O3 -DSTAR2 -o xorshift4096star2-stdout
${CC} -std=c99 -Wall xorshift4096.c -O3 -DSTAR2 -DREVERSE -o xorshift4096star2-rev-stdout

${CC} -std=c99 -Wall xsadd.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xsadd-crush-full
${CC} -std=c99 -Wall xsadd.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xsadd-rev-crush-full

${CC} -std=c99 -Wall well1024a.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o well1024a-crush-full
${CC} -std=c99 -Wall well1024a.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o well1024a-rev-crush-full
${CC} -std=c99 -Wall well1024a.c -O3  -o well1024a-stdout
${CC} -std=c99 -Wall well1024a.c -O3  -DREVERSE -o well1024a-rev-stdout

${CC} -std=c99 -Wall well19937a.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o well19937a-crush-full
${CC} -std=c99 -Wall well19937a.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o well19937a-rev-crush-full
${CC} -std=c99 -Wall well19937a.c -O3  -o well19937a-stdout
${CC} -std=c99 -Wall well19937a.c -O3  -DREVERSE -o well19937a-rev-stdout

${CC} -std=c99 -Wall mt19937.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o mt19937-crush-full
${CC} -std=c99 -Wall mt19937.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o mt19937-rev-crush-full
${CC} -std=c99 -Wall mt19937.c -O3 -o mt19937-stdout
${CC} -std=c99 -Wall mt19937.c -O3 -DREVERSE -o mt19937-rev-stdout

${CC} -std=c99 -Wall ran.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o ran-crush-full
${CC} -std=c99 -Wall ran.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o ran-rev-crush-full

${CC} -std=c99 -Wall jrand.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o jrand-crush-full
${CC} -std=c99 -Wall jrand.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o jrand-rev-crush-full
${CC} -std=c99 -Wall jrand.c -O3 -o jrand-stdout
${CC} -std=c99 -Wall jrand.c -O3 -DREVERSE -o jrand-rev-stdout

${CC} -std=c99 -Wall xorgens4096.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorgens4096-crush-full
${CC} -std=c99 -Wall xorgens4096.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o xorgens4096-rev-crush-full

${CC} -std=c99 -Wall -O3 xorgens4096.c -o xorgens4096-stdout
${CC} -std=c99 -Wall -O3 xorgens4096.c -DREVERSE -o xorgens4096-rev-stdout

${CC} -std=c99 -Wall murmurhash3.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o murmurhash3-crush-full
${CC} -std=c99 -Wall murmurhash3.c -O3 -I/usr/local/include  -I/usr/local/include/TestU01 -DTESTU01=bbattery_BigCrush -DREVERSE -L/usr/local/lib -lprobdist -lmylib -ltestu01 -o murmurhash3-rev-crush-full

${CC} -std=c99 -Wall -O3 murmurhash3.c -o murmurhash3-stdout
${CC} -std=c99 -Wall -O3 murmurhash3.c -DREVERSE -o murmurhash3-rev-stdout

${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 xorshift64-speed.c -O3 -o xorshift64-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 xorshift64star32-speed.c -O3 -o xorshift64star32-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 xorshift128plus-speed.c -O3 -o xorshift128plus-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 xorshift128star8-speed.c -O3 -o xorshift128star8-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 xorshift1024star32-speed.c -O3 -o xorshift1024star32-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 xorshift1024-speed.c -O3 -o xorshift1024-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 xorshift1024plus-speed.c -O3 -o xorshift1024plus-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 xorshift4096star32-speed.c -O3 -o xorshift4096star32-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 xorshift1024-speed.c -O3 -o xorshift1024-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 xorshift4096-speed.c -O3 -o xorshift4096-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 xorgens4096-speed.c -O3 -o xorgens4096-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 well1024a-speed.c -O3 -o well1024a-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 well19937a-speed.c -O3 -o well19937a-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 mt19937-speed.c -O3 -o mt19937-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 murmurhash3-speed.c -O3 -o murmurhash3-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 ran-speed.c -O3 -o ran-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 xsadd-speed.c -O3 -o xsadd-speed
${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 jrand-speed.c -O3 -o jrand-speed

${CC} -std=c99 -Wall -fomit-frame-pointer -msse4.2 loop-speed.c -O3 -o loop-speed

${CC} -std=c99 -O3 -DSTAR32 xorshift64-ez.c -o xorshift64star32-ez
${CC} -std=c99 -O3 -DSTAR8 xorshift64-ez.c -o xorshift64star8-ez
${CC} -std=c99 -O3 -DSTAR2 xorshift64-ez.c -o xorshift64star2-ez
${CC} -std=c99 -O3 -DSTAR8 xorshift1024-ez.c -o xorshift1024star8-ez
${CC} -std=c99 -O3 -DADD xorshift1024-ez.c -o xorshift1024plus-ez
${CC} -std=c99 -O3 -DSTAR2 xorshift4096-ez.c -o xorshift4096star2-ez
${CC} -std=c99 -O3 -DSTAR8 xorshift128-ez.c -o xorshift128star8-ez
${CC} -std=c99 -O3 -DADD xorshift128-ez.c -o xorshift128plus-ez
${CC} -std=c99 -O3 well19937a-ez.c -o well19937a-ez
${CC} -std=c99 -O3 well1024a-ez.c -o well1024a-ez
${CC} -std=c99 -O3 mt19937-ez.c -o mt19937-ez
${CC} -std=c99 -O3 xorgens4096-ez.c -o xorgens4096-ez
${CC} -std=c99 -O3 xsadd-ez.c -o xsadd-ez
