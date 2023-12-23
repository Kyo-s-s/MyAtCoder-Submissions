A, M, L, R = map(int, input().split())
low = (L - A + M - 1) // M
high = (R - A) // M
print(high - low + 1)