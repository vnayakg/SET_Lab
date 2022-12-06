def prettyPrint(*args):

    for i in args:
        print("%50.0d" % (i), end=' ')
    print()


def prettyPrintInverse(*args):

    for i in args:
        print("%30.0d" % (i), end=' ')
    print()


def prettyPrintExt(*args):

    for i in args:
        print("%20.0d" % (i), end=' ')
    print()


def euclidGCD(a, b):

    while b != 0:
        prev_a = a
        prev_b = b

        q = prev_a / prev_b
        a = prev_b
        b = prev_a % prev_b
        rem = b
        prettyPrint(q, prev_a, prev_b, rem)
    prettyPrint(-1, a, b, -1)

    print('-'*215, end='\n\n')
    return a


def multiplicativeInverse(a, b):
    t1 = 0
    t2 = 1

    while b != 0:
        rem = a % b
        q = a // b

        t = t1 - q*t2

        prettyPrintInverse(q, a, b, rem, t1, t2, t)

        t1 = t2
        t2 = t

        a = b
        b = rem
    print('-'*215, end='\n\n')
    return t1


def extendedEuclid(a, b):
    s1 = 1
    s2 = 0
    t1 = 0
    t2 = 1

    while b != 0:
        rem = a % b
        q = a // b

        s = s1 - q*s2
        t = t1 - q*t2

        prettyPrintExt(q, a, b, rem, s1, s2, s, t1, t2, t)
        s1 = s2
        s2 = s

        t1 = t2
        t2 = t

        a = b
        b = rem
    print('-'*215, end='\n\n')
    return s1, t1


if __name__ == "__main__":
    print("1. GCD using Euclid Algorithm")
    print("2. Extended Euclid Algorithm")
    print("3. Multiplicative Inverse\n")

    option = int(input("Enter your option > "))

    if option == 1:
        a = int(input("Enter value of a > "))
        b = int(input("Enter value of b > "))

        print(f'{"q" :>50}', f'{"a" :>50}', f'{"b" :>50}', f'{"r" :>50}')
        print('-'*215, end='\n\n')
        gcd = euclidGCD(a, b)

        print("GCD of a and b is > ", gcd)

    elif option == 2:
        a = int(input("Enter value of a > "))
        b = int(input("Enter value of b > "))

        print(f'{"q" :>20}', f'{"a" :>20}', f'{"b" :>20}', f'{"r" :>20}', f'{"s1" :>20}',
              f'{"s2" :>20}', f'{"s" :>20}' f'{"t1" :>20}', f'{"t2" :>20}', f'{"t" :>20}')
        print('-'*215)

        s, t = extendedEuclid(a, b)
        print("Values of s and t are >  ", s, ", ", t)

    elif option == 3:
        a = int(input("Enter value of a > "))
        b = int(input("Enter value of x in Zx > "))

        print(f'{"q" :>50}', f'{"a" :>50}', f'{"b" :>50}', f'{"r" :>50}')
        print('-'*215, end='\n\n')
        gcd = euclidGCD(a, b)

        if(gcd == 1):

            print(f'{"q" :>30}', f'{"a" :>30}', f'{"b" :>30}',
                  f'{"r" :>30}', f'{"t1" :>30}', f'{"t2" :>30}', f'{"t" :>30}')
            print('-'*215)
            t = multiplicativeInverse(a, b)

            print("Multiplicative inverse of ", a, " in Z of ", b, " is ", t)
            if t < 0:
                print("or ", b + t)
        else:
            print("Multiplicative inverse of ", a,
                  " in Z of ", b, " does not exist")
    else:
        print("Invalid option selected, exiting...")
