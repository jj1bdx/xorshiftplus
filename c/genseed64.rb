#!/usr/bin/ruby

n = ARGV[0].to_i

r = 1 << ( 64 * n )

100.times do |i|

	s = 1 + ( r / 100 ).floor * i
	n.times do |j|
		printf( "0x%x ", ( s >> ( ( n - 1 - j ) * 64 ) ) & 0xFFFFFFFFFFFFFFFF );
	end
	puts
end
