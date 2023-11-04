B = int(input())

A = 1
ans = -1
while True:
  if A ** A == B:
    ans = A
  if A ** A > B:
    break
  A += 1
  
print(ans)