from collections import defaultdict
M = 314159265358979

N = int(input())
A = [int(input()) % M for _ in range(N)]

C = defaultdict(int)
for a in A:
  C[a] += 1
  
ans = 0
for i in range(N):
  for j in range(N):
    ak = A[i] * A[j] % M
    if ak in C:
      ans += C[ak]
      
print(ans)
