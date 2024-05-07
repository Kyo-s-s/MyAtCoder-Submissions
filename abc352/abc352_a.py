N, X, Y, Z = map(int, input().split())
if X > Y:
    X, Y = Y, X
    
if X < Z and Z < Y:
    print("Yes")
else:
    print("No")
