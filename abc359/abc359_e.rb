n = gets.to_i
h = gets.split(" ").map { |x| x.to_i }

stack = []
sum = 0
ans = []
h.each do |a|
  w = 1
  while true
    if stack.empty?
      break
    end
    sh, sw = stack.last
    if sh < a
      sum -= sh * sw
      w += sw 
      stack.pop
    else
      break
    end
  end

  stack.append([a, w])
  sum += a * w

  ans.append sum + 1
end

puts ans.join(" ")