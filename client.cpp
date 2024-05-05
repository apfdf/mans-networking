
#include <sys/socket.h>
#include <bits/stdc++.h>
#include <arpa/inet.h>
using namespace std;

#define BUFFER_SIZE 1024

// outputs an error message and exits from the program
void error(string msg) {
    cerr << msg << endl;
    exit(1);
}

void sender(int client_socket) {

    while (true) {

        char buffer[BUFFER_SIZE] = {0};
        cin >> buffer;

        send(client_socket, buffer, strlen(buffer), 0);

    }

}

void reciever(int client_socket) {

    while (true) {
        
        char buffer[BUFFER_SIZE] = {0};
        recv(client_socket, buffer, sizeof(buffer), 0);

        cout << buffer << endl;

    }

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

    cout << "connected successfully" << endl;

    thread send_thread(sender, client_socket);
    thread recv_thread(reciever, client_socket);

    send_thread.join();
    recv_thread.join();

    while (true) {

        char buffer[1024] = {0};
        cin >> buffer;

        send(client_socket, buffer, strlen(buffer), 0);

    }

    // close the socket
    close(client_socket);

}
