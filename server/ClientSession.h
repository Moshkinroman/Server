#pragma once
#include "Authenticator.h"
#include "AuthDB.h"
#include "Logger.h"
#include "Calculator.h"
#include <string>
#include <vector>
#include <sys/socket.h>
#include <unistd.h>

class ClientSession {
public:
    ClientSession(int clientSocket, AuthDB& authDB, Logger& logger);
    ~ClientSession();
    
    void handle();
    
private:
    int clientSocket;
    AuthDB& authDB;
    Logger& logger;
    Authenticator authenticator;
    Calculator calculator;
    
    bool authenticate();
    void processData();
    
    void sendData(const void* data, size_t size);
    void recvData(void* data, size_t size);
    void sendString(const std::string& str);
    std::string recvString();
};
