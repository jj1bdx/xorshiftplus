#!/usr/bin/ruby

test_dir = ARGV[0] + "/"

prev_pattern = nil
i = 0
c = 0

r = {}
		
def r.to_s
	s = ""
	keys.sort.each do |name|
		s += name + " "
		res = []
		sum_p_values = 0
		c = 0
		near_1 = false
		self[name].each_pair do |p_value,count|
			# We normalize p-values so that "small is bad"
			if p_value > 0.5; then near_1 = true; end
			sum_p_values += ( p_value > 0.5 ? 1 - p_value : p_value ) * count
			c += count
		end
		sum_p_values /= c
		if sum_p_values > 1; then $stderr.puts("Probability exceeds one in " + name + ": " + sum_p_values.to_s); exit 1; end
		s += sprintf("(%d: %.3e%s) ", c, sum_p_values, near_1 ? " *" : "");
	end
	s
end

Dir.entries( test_dir ).each do |name| # The directories
	if name =~ /\.\.?$/; then next; end # Skip . and ..
	i = 0		
	c = 0
	r.clear		
	
	if File.exists?( test_dir + name ); then
		Dir.entries( test_dir + name ).each do |f|
			if f =~ /\.\.?$/; then next; end # Skip . and ..
			in_summary = false
			in_list = false
			File.open( test_dir + name + "/" + f ) do |file| # With this syntax we do not have to close the file
				while( l = file.gets ) 
					if in_list and l =~ /--------/; then in_list = in_summary = false; end
					if in_list; then
						test_name = l[0..34].strip.squeeze(" ").split(/ /)[1..-1].join("")
						p_value_string = l[34..-1].strip.squeeze(" ")
						p_value = 
							case p_value_string
								when "eps" then 1E-300
								when "eps1" then 1E-15
								when "1 - eps" then 1 - 1E-300
								when "1 - eps1" then 1 - 1E-15
								else eval(p_value_string)
							end
						if ! r[test_name]; then r[test_name] = {}; r[test_name].default = 0; end # Create new failed test if necessary
						r[test_name][p_value] += 1
						c += 1
					end # Here we count failed tests
					if in_summary and l =~ /--------/; then in_list = true; end
					if l =~ /Summary/; then in_summary = true; end
				end
			end
		end

		puts(name + "\t" + c.to_s + "\t" + r.to_s)

	end	
end

