def main():
    S = str(input())
    T = ""

    for s in S:
        if s not in "aiueo":
            T += s
    
    print(T)
    
  
        


if __name__ == '__main__':
    main()
    