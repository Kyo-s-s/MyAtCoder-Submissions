def main():
    N, T = map(int, input().split())
    A = [int(input()) for _ in range(N)]
    
    ans = 0
    bef = -1
    for a in A:
        if bef == -1:
            bef = a
        else:
            ans += min(T, a - bef)
            bef = a

    ans += T

    print(ans)





    


if __name__ == '__main__':
    main()
