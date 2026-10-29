#pragma once
#include "CLI.h"
#include "Logger.h"
#include "NetworkServer.h"
#include "AuthDB.h"
#include "ClientSession.h"
#include <memory>

class ServerApp {
public:
    ServerApp() = default;
    
    void run(int argc, char* argv[]);
    
private:
    CLI cli;
    std::unique_ptr<Logger> logger;
    NetworkServer networkServer;
    AuthDB authDB;
};
