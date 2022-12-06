"""
    57148506958055245395186612446559651557240272824407
    13658650467616482229787332356271505583389864123171
"""
#     p = 17887817633354987574556281477286444367299124242861
#     q = 27268642641181134095841690197249359439527837285619


def getGcd(a, b):
    r1 = 0
    r2 = 0

    r1 = a
    r2 = b

    while(r2 > 0):
        q = r1 // r2
        r = r1 - q * r2
        r1 = r2
        r2 = r
    return r1


def multiplicative_invers(a, n):
    r1 = n
    r2 = a

    t1 = 0
    t2 = 1

    while r2 > 0:
        q = r1 // r2
        r = r1 - q * r2
        t = t1 - q * t2

        r1 = r2
        r2 = r

        t1 = t2
        t2 = t

    return t1


def keyGeneration(p, q):

    print("Generating key pair\n")
    n = p * q
    print("value of n = ", n, '\n\n')
    phin = (p - 1) * (q - 1)
    print("value of phi = ", phin, '\n\n')

    pubKey = -1
    for i in range(2, phin):
        if getGcd(i, phin) == 1:
            pubKey = i
            break

    if pubKey == -1:
        raise Exception("Does not find any num with gcd(num, phi) == 1")

    priKey = (multiplicative_invers(pubKey, phin) + phin) % phin

    return pubKey, priKey, n


def power(x, y, p):

    res = 1  # Initialize result

    x = x % p  # Update x if it is more
    # than or equal to p

    while (y > 0):

        # If y is odd, multiply x with result
        if (y & 1):
            res = (res * x) % p

        # y must be even now
        y = y >> 1  # y = y/2
        x = (x * x) % p

    return res


def rsa_encrypt(message, e, n):
    plainNums = list(map(ord, message))
    cipherNums = []
    print(plainNums)
    print(e, n)
    for M in plainNums:
        cipherNums.append(power(M, e, n))

    return ' '.join(map(str, cipherNums))


def rsa_decrypt(cipher, d, n):
    cipherNums = list(map(int, cipher.split()))
    plainNums = []
    print(cipherNums)
    for C in cipherNums:
        plainNums.append(power(C, d, n))
    print(plainNums)
    return ''.join(map(chr, plainNums))


if __name__ == "__main__":
    e = None
    d = None
    n = None

    while True:
        print('\n\nRSA Algorithm:')
        print('1. Generate Keys')
        print('2. Encrypt')
        print('3. Decrypt')
        print('4. Exit')

        choice = int(input('Enter your choice: '))

        if choice == 1:
            print("\nEnter the first Prime Number(p): ")
            p = (int)(input())

            print("\nEnter Second Prime Number(q): ")
            q = (int)(input())

            e, d, n = keyGeneration(p, q)

            print('\nPrivate Key: [d,n] --> ({},{})\n\n'.format(d, n))
            print('\nPublic Key: [e,n] --> ({},{})\n\n'.format(e, n))

        elif choice == 2:
            plaintext = input('Enter plaintext: ')

            ciphertext = rsa_encrypt(plaintext, e, n)
            print("\n\nCipher Text: ", ciphertext)
        elif choice == 3:
            ciphertext = input('Enter ciphertext: ')
            plaintext = rsa_decrypt(ciphertext, d, n)
            print("\n\nPlain Text: ", plaintext)

        elif choice == 4:
            break
        else:
            print("\n\nInvalid choice")
