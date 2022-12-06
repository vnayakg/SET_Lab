from audioop import mul


def euclidGCD(a, b):

    while b != 0:
        prev_a = a
        prev_b = b

        q = prev_a / prev_b
        a = prev_b
        b = prev_a % prev_b
        rem = b
    return a


def multiplicativeInverse(a, n):
    r1 = n
    r2 = a

    t1 = 0
    t2 = 1

    while r2 > 0:
        r = r1 % r2
        q = r1 // r2

        t = t1 - q * t2
        t1 = t2
        t2 = t

        r1 = r2
        r2 = r

    if(t1 < 0):
        t1 = t1 + n

    return t1


def solveCRT(equations):
    print("Given Equations are: \n")
    for eq in equations:
        print(f'X = {eq["a"]} mod {eq["m"]}')
    print('\n')
    M = 1
    for eq in equations:
        M *= eq['m']

    print(f"M: {M}\n")
    M_values = []

    for eq in equations:
        M_values.append(M//eq['m'])

    print(f"M_values: {M_values}\n")
    inverse = []

    for i in range(len(equations)):
        m_i = equations[i]['m']
        M_i = M_values[i]

        if euclidGCD(m_i, M_i) != 1:
            raise Exception("Inverse does not exist or wrong equations")

        inverse.append(multiplicativeInverse(M_i, m_i))
    print(f"Inverse Values: {inverse}\n")
    res = 0

    for i in range(len(equations)):
        a = equations[i]['a']
        inv = inverse[i]
        curr_M = M_values[i]

        res += a*inv*curr_M

    return res % M


n = int(input("Enter number of equations: "))

print(f'\n---- Enter {n} equations as ->  a m (X = a mod m) ----\n')
equations = []

for i in range(n):
    print(f'equation {i+1}: \n')
    a = int(input("Enter value of a: "))
    m = int(input("Enter value of m: "))
    print()
    equations.append({"a": a, "m": m})

#equations = [{"a": 1, "m": 5}, {"a": 1, "m": 7}, {"a": 3, "m": 11}]
print("Value of X: ", solveCRT(equations))
