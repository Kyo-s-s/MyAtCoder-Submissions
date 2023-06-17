A = list(map(int, input().split()))

A = A[::-1]

ans = 0
for a in A:
    ans *= 2
    ans += a

print(ans)