import socket
import pickle
import time

from math import sqrt


def pow(x, y):
    # Initialize result
    res = 1

    while (y > 0):

        # If y is odd, multiply x with result
        if ((y & 1) != 0):
            res = res * x

        # y must be even now
        y = y >> 1  # y = y/2
        x = x * x  # Change x to x^2

    return res


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


def findPrimefactors(s, n):

    # Print the number of 2s that divide n
    while (n % 2 == 0):
        s.add(2)
        n = n // 2

    # n must be odd at this point. So we can
    # skip one element (Note i = i +2)
    for i in range(3, int(sqrt(n)), 2):

        # While i divides n, print i and divide n
        while (n % i == 0):

            s.add(i)
            n = n // i

    # This condition is to handle the case
    # when n is a prime number greater than 2
    if (n > 2):
        s.add(n)


def findPrimitive(n):
    s = set()

    # Check if n is prime or not
    # if (isPrime(n) == False):
    #     return -1

    # Find value of Euler Totient function
    # of n. Since n is a prime number, the
    # value of Euler Totient function is n-1
    # as there are n-1 relatively prime numbers.
    phi = n - 1

    # Find prime factors of phi and store in a set
    findPrimefactors(s, phi)

    # Check for every number from 2 to phi
    for r in range(2, phi + 1):

        # Iterate through all prime factors of phi.
        # and check if we found a power with value 1
        flag = False
        for it in s:

            # Check if r^((phi)/primefactors)
            # mod n is 1 or not
            if (power(r, phi // it, n) == 1):

                flag = True
                break

        # If there was no power with value 1.
        if (flag == False):
            return r

    # If no primitive root found
    return -1


def client_program():
    host = socket.gethostname()  # as both code is running on same pc
    port = 5005  # socket server port number

    client_socket = socket.socket()  # instantiate
    client_socket.connect((host, port))  # connect to the server
    print("Client Runing on ", client_socket.getsockname())

    # decide public values q and alpha
    p = int(input("\nEnter prime number q: "))  # take input
    print(f"\n> Calculating primitive root of {p}")
    pr = findPrimitive(p)
    print(f'\n> {pr} is primitive root of {p}')

    # send calculated public values to server
    id = 1
    data = {'q': p, 'pr': pr, 'id': id}
    print(f'\n{id} > Sending public values q and alpha to server')
    client_socket.send(pickle.dumps(data))   # 1. send message
    print(f"\n> Sent p and alpha (both public) to server: {data}\n")

    alpha = data['pr']
    q = data['q']

    # Receive Ya from server
    print(f"\n> Receiving Ya from server....")
    data = pickle.loads(client_socket.recv(1024))  # receive response
    ya = data['ya']
    id = data['id']
    print(f'\n{id} > Received Ya as {ya} from server')  # show in terminal
    time.sleep(1)

    # calculate Xb and Yb
    xb = int(input("Enter Server private key Xb = "))
    print(f'\n> Client private value ie Xb is {xb}')
    yb = power(alpha, xb, q)

    # Send Yb to server
    id = id + 1
    y = {'yb': yb, 'id': id}
    print(f'\n{id} > Sending yb value to server...')
    client_socket.send(pickle.dumps(y))
    time.sleep(1)

    # Calculate key
    print('\n> Calculating key.....')
    key = power(ya, xb, q)
    print(f'\n> Shared key =  {key}')

    print('\n\nExiting...')
    client_socket.close()  # close the connection


if __name__ == '__main__':
    client_program()
