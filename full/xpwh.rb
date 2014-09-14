#!/usr/bin/ruby

require "rational"

n = ARGV.size == 0 ? 1 : ARGV[0].to_i # number of output files

f = 0

for a in 1..63 do 
	for b in 1..(64-a) do 
		if a.gcd(b) != 1; then next; end
		for c in 1..63 do 
			prefix = n == 1 ? "" : ( (f.to_s) + "\t" )
			f = ( f + 1 ) % n
			printf("%s[m]:=[1]*(x^2) + ([1]+[l]^%d)*([1]+[r]^%s) + ([1]+[r]^%d)*x;\n", prefix , a, b, c )
			printf("%sp:=Det[m];\n", prefix);
			printf("%sirr:=Irred(p);\n", prefix)
			printf("%s!!('%d-%d-%d ', p, ' ', irr);\n", prefix, a, b, c)
		end
	end
end
