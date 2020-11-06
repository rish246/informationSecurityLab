#include <iostream>
#include <vector>

#include <math.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <sys/types.h>

using namespace std;

#define n 997
#define g 7

const int PORT = 5400;

uint64_t calc_mod(uint64_t base, uint64_t power, uint64_t mod)
{
    if (power == 0)
        return 1;

    if (power == 1)
        return base;

    int mid = (power / 2);

    int res = calc_mod(base, mid, mod);

    res = (res * res) % mod;

    if (power & 1)
        res = (res * base) % mod;

    return (res);
}

void exchange_keys(int client_socket)
{
    uint64_t x = rand() % 1000;

    uint64_t X = calc_mod(g, x, n);

    send(client_socket, &X, sizeof(X), 0);

    uint64_t Y = -1;

    recv(client_socket, &Y, sizeof(Y), 0);

    // NICE
    uint64_t secret = calc_mod(Y, X, n);

    cout << "The secret is : " << secret << endl;
}

void get_served(int client_socket)
{
    char paul_message[2048];

    recv(client_socket, &paul_message, sizeof(paul_message), 0);

    cout << "Paul sent a message : " << string(paul_message) << endl;

    char bob_message[2048] = "Hello Paul";

    send(client_socket, bob_message, sizeof(bob_message), 0);

    exchange_keys(client_socket);
}

int main()
{

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_address{};
    server_address.sin_port = htons(PORT);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;

    // connect
    if (connect(client_socket, (sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        cerr << "Couldn't connect to server" << endl;
        return -1;
    }

    cout << "Connected to the server" << endl;

    get_served(client_socket);

    // send requests to bob
}