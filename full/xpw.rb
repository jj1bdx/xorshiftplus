#!/usr/bin/ruby

$stdin.each do |t|
	s = t.chop.split(/\s+/)
	s0 = s[0].to_i
	s1 = s[1].to_i
	s2 = s[2].to_i

	printf("[m]:=([1]+[l]^%d)*([1]+[r]^%d)*([1]+[l]^%d);\n", s0, s1, s2)
	printf("p:=Chpoly([m]);\n")
	printf("!!('0.%d-%d-%d ', p);\n", s0, s1, s2)
	printf("[m]:=([1]+[r]^%d)*([1]+[l]^%d)*([1]+[r]^%d);\n", s0, s1, s2);
	printf("p:=Chpoly([m]);\n")
	printf("!!('1.%d-%d-%d ', p);\n", s0, s1, s2)
	printf("[m]:=([1]+[l]^%d)*([1]+[r]^%d)*([1]+[l]^%d);\n", s2, s1, s0);
	printf("p:=Chpoly([m]);\n")
	printf("!!('2.%d-%d-%d ', p);\n", s0, s1, s2)
	printf("[m]:=([1]+[r]^%d)*([1]+[l]^%d)*([1]+[r]^%d);\n", s2, s1, s0);
	printf("p:=Chpoly([m]);\n")
	printf("!!('3.%d-%d-%d ', p);\n", s0, s1, s2)
	printf("[m]:=([1]+[l]^%d)*([1]+[l]^%d)*([1]+[r]^%d);\n", s0, s2, s1);
	printf("p:=Chpoly([m]);\n")
	printf("!!('4.%d-%d-%d ', p);\n", s0, s1, s2)
	printf("[m]:=([1]+[r]^%d)*([1]+[r]^%d)*([1]+[l]^%d);\n", s0, s2, s1);
	printf("p:=Chpoly([m]);\n")
	printf("!!('5.%d-%d-%d ', p);\n", s0, s1, s2)
	printf("[m]:=([1]+[r]^%d)*([1]+[l]^%d)*([1]+[l]^%d);\n", s1, s0, s2);
	printf("p:=Chpoly([m]);\n")
	printf("!!('6.%d-%d-%d ', p);\n", s0, s1, s2)
	printf("[m]:=([1]+[l]^%d)*([1]+[r]^%d)*([1]+[r]^%d);\n", s1, s0, s2);
	printf("p:=Chpoly([m]);\n")
	printf("!!('7.%d-%d-%d ', p);\n", s0, s1, s2)
end
