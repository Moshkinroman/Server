#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdexcept>
#include <memory>

class NetworkServer {
public:
    NetworkServer() = default;
    ~NetworkServer();
    
    void bind(int port);
    int accept();
    void close();
    
private:
    int serverSocket = -1;
};
