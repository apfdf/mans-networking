
#include <sys/socket.h>
#include <bits/stdc++.h>
#include <arpa/inet.h>
using namespace std;

// outputs an error message and exits from the program
void error(string msg) {
    cerr << msg << endl;
    exit(1);
}

int main(int argc, char* argv[]) {

    // create client socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying server address
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // request connection from cli  ent_socket to the address of the server
    connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    vector<char> buf(1024);
    while (true) {

        recv(client_socket, buf.data(), buf.size(), 0);
        cout << buf.data() << endl;

    }

    // close the socket
    close(client_socket);

}
