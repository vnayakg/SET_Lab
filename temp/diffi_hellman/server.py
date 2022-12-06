import socket
import pickle
import random
import time


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

def server_program():
    # get the hostname
    host = socket.gethostname()
    port = 5005  # initiate port no above 1024

    server_socket = socket.socket()  # get instance
    # look closely. The bind() function takes tuple as argument
    server_socket.bind((host, port))  # bind host address and port together

    # configure how many client the server can listen simultaneously
    server_socket.listen(1)
    print(f'[STARTING] Server listening on port {port}')
    conn, address = server_socket.accept()  # accept new connection
    print("> Connection from: " + str(address))

    # receive q and alpha from client
    print('\n> Waiting...')
    data = pickle.loads(conn.recv(1024))  # 1.
    id = data['id']
    print(f"\n{id} > Received p and alpha (both public) from client: {data}\n")

    alpha = data['pr']
    q = data['q']

    # calculate xa and ya
    xa = int(input("Enter Server private key Xa = "))
    print(f'\n> Server private value ie Xa is {xa}')
    ya = power(alpha, xa, q)

    # send ya to client
    id = id + 1
    y = {"ya": ya, 'id': id}
    print(f'\n{id} > Sending ya value to client...')
    conn.send(pickle.dumps(y))  # send data to the client
    time.sleep(1)

    # receive yb from client
    data = pickle.loads(conn.recv(1024))
    yb = data['yb']
    id = data['id']
    print(f'\n{id} > Received Yb as {yb} from client')
    time.sleep(1)

    # calculate key
    print('\n> Calculating key.....')
    key = power(yb, xa, q)
    print(f'\n> Shared key =  {key}')

    print('\n\nExiting...')
    conn.close()  # close the connection


if __name__ == '__main__':
    server_program()
