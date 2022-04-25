def main():
    
    N = int(input())
    dist = {}
    for _ in range(N):
        s = str(input())
        if s in dist:
            dist[s] += 1
        else:
            dist[s] = 1

    ma = 0
    ans = ""
    for k in dist:
        if dist[k] > ma:
            ma = dist[k]
            ans = k

    print(ans)
        



if __name__ == '__main__':
    main()
