N = int(input())

ans = False

for x in range(0, 100):
  for y in range(0, 100):
    if 2 ** x * 3 ** y == N:
      ans = True
      
if (ans):
  print("Yes")
else:
  print("No")