
#include <sys/socket.h>
#include <bits/stdc++.h>
#include <arpa/inet.h>
using namespace std;

#define QUEUE_SIZE 10
#define BUFFER_SIZE 1024

// outputs an error message and exits from the program
void error(string msg) {
    cerr << msg << endl;
    exit(1);
}

// awaits messages from a specific client and sends to all other clients
void client_com(int com_client_socket, vector<int>* client_sockets, mutex* client_sockets_m) {

    cout << "com thread started" << endl;

    char username[BUFFER_SIZE] = {0};
    recv(com_client_socket, username, sizeof(username), 0);
    if (!username[0]) {
        return;
    }

    while (true) {

        char buffer[BUFFER_SIZE] = {0};
        recv(com_client_socket, buffer, sizeof(buffer), 0);

        if (!buffer[0]) {
            cout << "client disconnected" << endl;
            break;
        }

        string mes = (string)username + ": " + (string)buffer;

        (*client_sockets_m).lock();
        for (int client_socket : *client_sockets) {
            if (client_socket != com_client_socket) {
                send(client_socket, mes.c_str(), strlen(mes.c_str()), 0);
            }
        }
        (*client_sockets_m).unlock();

    }

}

// function that listens on the server socket and creates a client_handler() thread every time it accepts a new connection.
void listener(int server_socket, vector<int>* client_sockets, mutex* client_sockets_m) {

    vector<thread> com_threads = {};

    while (true) {

        listen(server_socket, QUEUE_SIZE);
        int client_socket = accept(server_socket, nullptr, nullptr);

        (*client_sockets_m).lock();
        (*client_sockets).push_back(client_socket);
        (*client_sockets_m).unlock();

        cout << "client connected" << endl;

        com_threads.push_back(thread(client_com, client_socket, client_sockets, client_sockets_m));

    }

}

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
    mutex client_sockets_m;

    thread listen_thread(listener, server_socket, &client_sockets, &client_sockets_m);
    listen_thread.join();

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
