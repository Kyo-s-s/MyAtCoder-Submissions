(r, g, b) = gets.split(" ").map { |x| x.to_i }
c = gets

ans = if c == "Red\n"
        [g, b].min
      elsif c == "Green\n"
        [r, b].min
      else
        [g, r].min
      end

puts ans