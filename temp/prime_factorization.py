import math
import time


def primeFactors(n):
    arr = []
    # Print the number of two's that divide n
    while n % 2 == 0:
        # print(2)
        n = n / 2

    for i in range(3, int(math.sqrt(n))+1, 2):

        # print(i)
        while n % i == 0:
            # print("///////////////////////////////////////Prime factor is: ",i)
            arr.append(i)
            n = n / i

    # Condition if n is a prime
    # number greater than 2
    if n > 2:
        print(n)
    return arr
# Driver Program to test above function
 # 10 -> 10000252373 Time elapsed:  0.0038862228393554688
 # 12 -> 1000010666663 Time elapsed:  0.03688168525695801
 # 14 -> 100000008888889 Time elapsed:  0.3377974033355713
 # 16 -> 10000000058888887 Time elapsed:  3.871786594390869


semiprims = [100000000088787877679, 10000000000097987989, 1000000000099987889, 100000005178888819,
             10000000058888887, 1000000518888883, 100000008888889, 10000079888899, 1000010666663]
digit = [20, 19, 17, 18, 16, 15, 14, 13, 12]

for i in range(len(semiprims)-1, -1, -1):

    start = time.time()
    l = primeFactors(semiprims[i])
    end = time.time()

    print(l)
    print("Semiprime: ", semiprims[i])
    print("Number of digits: ", digit[i])
    print("Time elapsed: ", end - start)
    print()
