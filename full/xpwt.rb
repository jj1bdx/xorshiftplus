#!/usr/bin/ruby

require "rational"

for a in 1..63 do 
	for b in 1..(64-a) do 
		if a.gcd(b) != 1; then next; end
		for c in 1..63 do 
			printf("[m]:=[1]*(x^16) + ([1]+[l]^%d)*([1]+[r]^%s) + ([1]+[r]^%d)*(x^15);\n", a, b, c )
			printf("p:=Det[m];\n");
			printf("irr:=Irred(p);\n")
			printf("!!('%d-%d-%d ', p, ' ', irr);\n", a, b, c)
		end
	end
end
