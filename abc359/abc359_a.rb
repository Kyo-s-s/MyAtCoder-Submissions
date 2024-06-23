n = gets.to_i
ans = 0
n.times do 
  if gets == "Takahashi\n" 
    ans += 1
  end
end

puts ans