n, k = gets.split(" ").map { |x| x.to_i }
s = gets.chomp

mod = 998244353

dp = Hash.new(0)
dp[""] = 1

def new_str(str, c, k)
  res = str + c
  if res.length > k
    return res[1..-1]
  end
  res
end

ng_word = []

(1 << k).times do |msk|
  str = ""
  k.times do |i|
    if ((msk >> i) & 1) == 0
      str += "A"
    else
      str += "B"
    end
  end
  if str == str.reverse
    ng_word.append(str)
  end
end


s.split("").each do |c|
  pd = Hash.new(0)
  dp.each do |str, val|
    if c == "A" || c == "?"
      nstr = new_str(str, "A", k)
      pd[nstr] = (pd[nstr] + val) % mod
    end
    if c == "B" || c == "?"
      nstr = new_str(str, "B", k)
      pd[nstr] = (pd[nstr] + val) % mod
    end
  end
  ng_word.each do |ng|
    pd[ng] = 0
  end

  dp = pd
end

ans = 0
dp.each do |str, val|
  ans = (ans + val) % mod
end

puts ans
