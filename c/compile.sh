#!/bin/bash -e

gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -lprobdist -lmylib -ltestu01 -o xorshift64-crush-small

gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DSTAR32 -lprobdist -lmylib -ltestu01 -o xorshift64star32-crush-small
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DSTAR32 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift64star32-rev-crush-small
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DSTAR8 -lprobdist -lmylib -ltestu01 -o xorshift64star8-crush-small
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DSTAR8 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift64star8-rev-crush-small
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DSTAR2 -lprobdist -lmylib -ltestu01 -o xorshift64star2-crush-small
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DSTAR2 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift64star2-rev-crush-small
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DSTAR5 -lprobdist -lmylib -ltestu01 -o xorshift64star5-crush-small
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DSTAR5 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift64star5-rev-crush-small

gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DADD -lprobdist -lmylib -ltestu01 -o xorshift128plus-crush-small
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DADD -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift128plus-rev-crush-small

gcc -std=c99 -Wall xorshift116plus.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -lprobdist -lmylib -ltestu01 -o xorshift116plus-crush-small
gcc -std=c99 -Wall xorshift116plus.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift116plus-rev-crush-small

gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -lprobdist -lmylib -ltestu01 -o xorshift64-crush-medium

gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DSTAR32 -lprobdist -lmylib -ltestu01 -o xorshift64star32-crush-medium
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DSTAR32 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift64star32-rev-crush-medium
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DSTAR8 -lprobdist -lmylib -ltestu01 -o xorshift64star8-crush-medium
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DSTAR8 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift64star8-rev-crush-medium
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DSTAR2 -lprobdist -lmylib -ltestu01 -o xorshift64star2-crush-medium
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DSTAR2 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift64star2-rev-crush-medium
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DSTAR5 -lprobdist -lmylib -ltestu01 -o xorshift64star5-crush-medium
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DSTAR5 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift64star5-rev-crush-medium

gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DADD -lprobdist -lmylib -ltestu01 -o xorshift128plus-crush-medium
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DADD -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift128plus-rev-crush-medium

gcc -std=c99 -Wall xorshift116plus.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -lprobdist -lmylib -ltestu01 -o xorshift128plus-crush-medium
gcc -std=c99 -Wall xorshift116plus.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift128plus-rev-crush-medium

gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -lprobdist -lmylib -ltestu01 -o xorshift64-crush-full

gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR32 -lprobdist -lmylib -ltestu01 -o xorshift64star32-crush-full
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR32 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift64star32-rev-crush-full
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR8 -lprobdist -lmylib -ltestu01 -o xorshift64star8-crush-full
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR8 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift64star8-rev-crush-full
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR2 -lprobdist -lmylib -ltestu01 -o xorshift64star2-crush-full
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR2 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift64star2-rev-crush-full
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR5 -lprobdist -lmylib -ltestu01 -o xorshift64star5-crush-full
gcc -std=c99 -Wall xorshift64.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR5 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift64star5-rev-crush-full

gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DSTAR32 -lprobdist -lmylib -ltestu01 -o xorshift128star32-crush-small
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DSTAR32 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift128star32-rev-crush-small
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DSTAR8 -lprobdist -lmylib -ltestu01 -o xorshift128star8-crush-small
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DSTAR8 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift128star8-rev-crush-small
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DSTAR2 -lprobdist -lmylib -ltestu01 -o xorshift128star2-crush-small
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_SmallCrush -DSTAR2 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift128star2-rev-crush-small

gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DSTAR32 -lprobdist -lmylib -ltestu01 -o xorshift128star32-crush-medium
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DSTAR32 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift128star32-rev-crush-medium
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DSTAR8 -lprobdist -lmylib -ltestu01 -o xorshift128star8-crush-medium
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DSTAR8 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift128star8-rev-crush-medium
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DSTAR2 -lprobdist -lmylib -ltestu01 -o xorshift128star2-crush-medium
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_Crush -DSTAR2 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift128star2-rev-crush-medium

gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -lprobdist -lmylib -ltestu01 -o xorshift128-crush-full

gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR32 -lprobdist -lmylib -ltestu01 -o xorshift128star32-crush-full
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR32 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift128star32-rev-crush-full
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR8 -lprobdist -lmylib -ltestu01 -o xorshift128star8-crush-full
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR8 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift128star8-rev-crush-full
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR2 -lprobdist -lmylib -ltestu01 -o xorshift128star2-crush-full
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR2 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift128star2-rev-crush-full

gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DADD -lprobdist -lmylib -ltestu01 -o xorshift128plus-crush-full
gcc -std=c99 -Wall xorshift128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DADD -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift128plus-rev-crush-full

gcc -std=c99 -Wall xorshift116plus.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -lprobdist -lmylib -ltestu01 -o xorshift116plus-crush-full
gcc -std=c99 -Wall xorshift116plus.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift116plus-rev-crush-full

gcc -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -lprobdist -lmylib -ltestu01 -o xorshift1024-crush-full
gcc -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift1024-rev-crush-full

gcc -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR32 -lprobdist -lmylib -ltestu01 -o xorshift1024star32-crush-full
gcc -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR32 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift1024star32-rev-crush-full

gcc -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR8 -lprobdist -lmylib -ltestu01 -o xorshift1024star8-crush-full
gcc -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR8 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift1024star8-rev-crush-full

gcc -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR2 -lprobdist -lmylib -ltestu01 -o xorshift1024star2-crush-full
gcc -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR2 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift1024star2-rev-crush-full

gcc -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DADD -lprobdist -lmylib -ltestu01 -o xorshift1024plus-crush-full
gcc -std=c99 -Wall xorshift1024.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DADD -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift1024plus-rev-crush-full

gcc -std=c99 -Wall xorshift1024.c -O3 -DSTAR32 -o xorshift1024star32-stdout
gcc -std=c99 -Wall xorshift1024.c -O3 -DSTAR32 -DREVERSE -o xorshift1024star32-rev-stdout

gcc -std=c99 -Wall xorshift1024.c -O3 -DSTAR8 -o xorshift1024star8-stdout
gcc -std=c99 -Wall xorshift1024.c -O3 -DSTAR8 -DREVERSE -o xorshift1024star8-rev-stdout

gcc -std=c99 -Wall xorshift1024.c -O3 -DSTAR2 -o xorshift1024star2-stdout
gcc -std=c99 -Wall xorshift1024.c -O3 -DSTAR2 -DREVERSE -o xorshift1024star2-rev-stdout


gcc -std=c99 -Wall xorshift4096.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -lprobdist -lmylib -ltestu01 -o xorshift4096-crush-full
gcc -std=c99 -Wall xorshift4096.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift4096-rev-crush-full

gcc -std=c99 -Wall xorshift4096.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR32 -lprobdist -lmylib -ltestu01 -o xorshift4096star32-crush-full
gcc -std=c99 -Wall xorshift4096.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR32 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift4096star32-rev-crush-full

gcc -std=c99 -Wall xorshift4096.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR8 -lprobdist -lmylib -ltestu01 -o xorshift4096star8-crush-full
gcc -std=c99 -Wall xorshift4096.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR8 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift4096star8-rev-crush-full

gcc -std=c99 -Wall xorshift4096.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR2 -lprobdist -lmylib -ltestu01 -o xorshift4096star2-crush-full
gcc -std=c99 -Wall xorshift4096.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DSTAR2 -DREVERSE -lprobdist -lmylib -ltestu01 -o xorshift4096star2-rev-crush-full

gcc -std=c99 -Wall xorshift4096.c -O3 -DSTAR32 -o xorshift4096star32-stdout
gcc -std=c99 -Wall xorshift4096.c -O3 -DSTAR32 -DREVERSE -o xorshift4096star32-rev-stdout

gcc -std=c99 -Wall xorshift4096.c -O3 -DSTAR8 -o xorshift4096star8-stdout
gcc -std=c99 -Wall xorshift4096.c -O3 -DSTAR8 -DREVERSE -o xorshift4096star8-rev-stdout

gcc -std=c99 -Wall xorshift4096.c -O3 -DSTAR2 -o xorshift4096star2-stdout
gcc -std=c99 -Wall xorshift4096.c -O3 -DSTAR2 -DREVERSE -o xorshift4096star2-rev-stdout

gcc -std=c99 -Wall xsadd.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -lprobdist -lmylib -ltestu01 -o xsadd-crush-full
gcc -std=c99 -Wall xsadd.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DREVERSE -lprobdist -lmylib -ltestu01 -o xsadd-rev-crush-full

gcc -std=c99 -Wall well1024a.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -lprobdist -lmylib -ltestu01 -o well1024a-crush-full
gcc -std=c99 -Wall well1024a.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DREVERSE -lprobdist -lmylib -ltestu01 -o well1024a-rev-crush-full
gcc -std=c99 -Wall well1024a.c -O3  -o well1024a-stdout
gcc -std=c99 -Wall well1024a.c -O3  -DREVERSE -o well1024a-rev-stdout

gcc -std=c99 -Wall well19937a.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -lprobdist -lmylib -ltestu01 -o well19937a-crush-full
gcc -std=c99 -Wall well19937a.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DREVERSE -lprobdist -lmylib -ltestu01 -o well19937a-rev-crush-full
gcc -std=c99 -Wall well19937a.c -O3  -o well19937a-stdout
gcc -std=c99 -Wall well19937a.c -O3  -DREVERSE -o well19937a-rev-stdout

gcc -std=c99 -Wall mt19937.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -lprobdist -lmylib -ltestu01 -o mt19937-crush-full
gcc -std=c99 -Wall mt19937.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DREVERSE -lprobdist -lmylib -ltestu01 -o mt19937-rev-crush-full
gcc -std=c99 -Wall mt19937.c -O3 -o mt19937-stdout
gcc -std=c99 -Wall mt19937.c -O3 -DREVERSE -o mt19937-rev-stdout

gcc -std=c99 -Wall ran.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -lprobdist -lmylib -ltestu01 -o ran-crush-full
gcc -std=c99 -Wall ran.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DREVERSE -lprobdist -lmylib -ltestu01 -o ran-rev-crush-full

gcc -std=c99 -Wall jrand.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -lprobdist -lmylib -ltestu01 -o jrand-crush-full
gcc -std=c99 -Wall jrand.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DREVERSE -lprobdist -lmylib -ltestu01 -o jrand-rev-crush-full
gcc -std=c99 -Wall jrand.c -O3 -o jrand-stdout
gcc -std=c99 -Wall jrand.c -O3 -DREVERSE -o jrand-rev-stdout

gcc -std=c99 -Wall xorgens4096.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -lprobdist -lmylib -ltestu01 -o xorgens4096-crush-full
gcc -std=c99 -Wall xorgens4096.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DREVERSE -lprobdist -lmylib -ltestu01 -o xorgens4096-rev-crush-full

gcc -std=c99 -Wall -O3 xorgens4096.c -o xorgens4096-stdout
gcc -std=c99 -Wall -O3 xorgens4096.c -DREVERSE -o xorgens4096-rev-stdout

gcc -std=c99 -Wall splitmix.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -lprobdist -lmylib -ltestu01 -o splitmix-crush-full
gcc -std=c99 -Wall splitmix.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DREVERSE -lprobdist -lmylib -ltestu01 -o splitmix-rev-crush-full

gcc -std=c99 -Wall mcg128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -lprobdist -lmylib -ltestu01 -o mcg128-crush-full
gcc -std=c99 -Wall mcg128.c -O3 -I/usr/local/include  -DTESTU01=bbattery_BigCrush -DREVERSE -lprobdist -lmylib -ltestu01 -o mcg128-rev-crush-full

gcc -std=c99 -O3 -DSTAR32 xorshift64-ez.c -o xorshift64star32-ez
gcc -std=c99 -O3 -DSTAR8 xorshift64-ez.c -o xorshift64star8-ez
gcc -std=c99 -O3 -DSTAR2 xorshift64-ez.c -o xorshift64star2-ez
gcc -std=c99 -O3 -DSTAR8 xorshift1024-ez.c -o xorshift1024star8-ez
gcc -std=c99 -O3 -DADD xorshift1024-ez.c -o xorshift1024plus-ez
gcc -std=c99 -O3 -DSTAR2 xorshift4096-ez.c -o xorshift4096star2-ez
gcc -std=c99 -O3 -DSTAR8 xorshift128-ez.c -o xorshift128star8-ez
gcc -std=c99 -O3 -DADD xorshift128-ez.c -o xorshift128plus-ez
gcc -std=c99 -O3 well19937a-ez.c -o well19937a-ez
gcc -std=c99 -O3 well1024a-ez.c -o well1024a-ez
gcc -std=c99 -O3 mt19937-ez.c -o mt19937-ez
gcc -std=c99 -O3 xorgens4096-ez.c -o xorgens4096-ez
gcc -std=c99 -O3 xsadd-ez.c -o xsadd-ez

gcc -std=c99 -Wall xorshift64-check.c -O3 -o xorshift64-check

gcc -std=c99 -Wall xorshift64-check.c -O3 -DSTAR32 -o xorshift64star32-check
gcc -std=c99 -Wall xorshift64-check.c -O3 -DSTAR32 -DREVERSE -o xorshift64star32-rev-check
gcc -std=c99 -Wall xorshift64-check.c -O3 -DSTAR8 -o xorshift64star8-check
gcc -std=c99 -Wall xorshift64-check.c -O3 -DSTAR8 -DREVERSE -o xorshift64star8-rev-check
gcc -std=c99 -Wall xorshift64-check.c -O3 -DSTAR2 -o xorshift64star2-check
gcc -std=c99 -Wall xorshift64-check.c -O3 -DSTAR2 -DREVERSE -o xorshift64star2-rev-check
