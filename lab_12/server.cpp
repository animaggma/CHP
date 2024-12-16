#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <mutex>

#define PORT 5000
#define BUFFER_SIZE 1024

std::mutex recv_lock; 

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};

    while (true) {
        std::lock_guard<std::mutex> lock(recv_lock); 
        int bytesRead = read(client_socket, buffer, BUFFER_SIZE);
        if (bytesRead <= 0) {
            std::cerr << "Client disconnected or read error" << std::endl;
            break;
        }

        std::cout << "Message received: " << buffer << std::endl;

        const char* response = "Server: Message received!";
        send(client_socket, response, strlen(response), 0);
        std::cout << "Response sent to client." << std::endl;
    }

    close(client_socket);
}

int main() {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    while (true) {
        int new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        std::cout << "New client connected." << std::endl;
        std::thread client_thread(handle_client, new_socket);
        client_thread.detach();  
    }

    close(server_fd);
    return 0;
}
