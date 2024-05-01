
#include <sys/socket.h>
#include <bits/stdc++.h>
#include <arpa/inet.h>
using namespace std;

#define QUEUE_SIZE 10

// outputs an error message and exits from the program
void error(string msg) {
    cerr << msg << endl;
    exit(1);
}

/*

// handles communication between server and a specific client. Should terminate itself when client disconnects.
void client_handler(int client_socket, vector<int>& client_sockets) {

    char buffer[1024];

    while (recv(client_socket, buffer, sizeof(buffer), 0) == 0) {
        for (int client_socket : client_sockets) {
            send(client_socket, buffer, strlen(buffer), 0);
        }
    }

}

// function that listens on the server socket and creates a client_handler() thread every time it accepts a new connection.
void listener(int server_socket, vector<int>& client_sockets) {
    
    while (true) {

        listen(server_socket, QUEUE_SIZE);
        int client_socket = accept(server_socket, nullptr, nullptr);
        client_sockets.push_back(client_socket);

        thread com_thread(client_handler, client_socket, client_sockets);

    }

}

*/

int main(int argc, char* argv[]) {

    // create the server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying the server address
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the server socket to its address
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    vector<int> client_sockets = {};

    //thread listen_thread(listener, server_socket, client_sockets);

    //listen_thread.join();

    while (true) {}



    /*

    // listen to incoming connections
    listen(server_socket, QUEUE_SIZE);

    // accept connection from client
    int client_socket = accept(server_socket, nullptr, nullptr);

    // recieve message from client
    char buffer[1024] = {0};
    recv(client_socket, buffer, sizeof(buffer), 0);
    cout << "message from client: " << buffer << endl;

    */

    // close the server socket
    close(server_socket);

}
