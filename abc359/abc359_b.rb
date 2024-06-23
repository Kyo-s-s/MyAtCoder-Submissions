n = gets.to_i
a = gets.split(" ").map { |x| x.to_i }

ans = 0
for i in 1..(2 * n - 1)
  if a[i - 1] == a [i + 1]
    ans += 1
  end
end

puts ans
