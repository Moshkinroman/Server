#include "NetworkServer.h"
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

NetworkServer::~NetworkServer() {
    close();
}

void NetworkServer::bind(int port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw std::runtime_error("Socket creation failed");
    }
    
    struct sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    
    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    if (::bind(serverSocket, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        throw std::runtime_error("Bind failed");
    }
    
    if (listen(serverSocket, 10) == -1) {
        throw std::runtime_error("Listen failed");
    }
}

int NetworkServer::accept() {
    struct sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    
    int clientSocket = ::accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
    if (clientSocket == -1) {
        throw std::runtime_error("Accept failed");
    }
    
    return clientSocket;
}

void NetworkServer::close() {
    if (serverSocket != -1) {
        ::close(serverSocket);
        serverSocket = -1;
    }
}
