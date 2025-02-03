#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 7777

int main() {
    int sock = 0;
    struct sockaddr_in server_address;
    char buffer[1024] = {0};

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "Error creating socket!" << std::endl;
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        std::cout << "Error serveraddress!" << std::endl;
        return -1;
    }

    if(connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cout << "Error connection server!" << std::endl;
        return -1;
    }

    std::string message;

    while(true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = read(sock, buffer, 1024);
        if(bytes > 0) std::cout << buffer << std::endl;
        else {
            std::cout << "Error get message from server." << std::endl;
            exit(1);
        }

        std::getline(std::cin, message);
        if(message == "endl") {
            std::cout << "Exit from program." << std::endl;
            exit(1);
        }

        send(sock, message.c_str(), message.length(), 0);
    }
    close(sock);
    return 0;
}