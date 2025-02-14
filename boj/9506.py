while True: 
    n = int(input())
    if (n == -1):
        break
    sum = 0
    for i in range(1, n):
        if n % i == 0 : 
            sum += i

    if sum != n: 
        print (f'{n} is NOT perfect.')
    else:
        print (f'{n} = 1', end = '')
        for i in range(2, n):
            if n % i == 0:
                print (f' + {i}', end = '')
        print ()