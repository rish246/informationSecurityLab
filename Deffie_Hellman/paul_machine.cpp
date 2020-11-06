#include <iostream>
#include <vector>
#include <string.h>

#include <math.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

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
    uint64_t y = rand() % 1000;

    uint64_t Y = calc_mod(g, y, n);

    uint64_t X = -1;

    recv(client_socket, &X, sizeof(X), 0);
    // send Y
    send(client_socket, &Y, sizeof(Y), 0);

    uint64_t secret = calc_mod(X, Y, n);

    cout << "The secret is : " << secret << endl;
}

void serve_client(int client_socket)
{
    char server_response[] = "Hello bob";

    send(client_socket, server_response, sizeof(server_response), 0);

    char bob_message[2048];

    recv(client_socket, &bob_message, sizeof(bob_message), 0);

    cout << "Bob sent a message : " << string(bob_message) << endl;

    exchange_keys(client_socket);
}

int main()
{

    // initialize a communication
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // struct
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind
    bind(server_socket, (sockaddr *)&server_address, sizeof(server_address));

    // accept
    listen(server_socket, 5);

    printf("Listening at port %d\n", PORT);

    while (true)
    {
        int client_socket = accept(server_socket, nullptr, nullptr);
        serve_client(client_socket);
        close(client_socket);
    }
}