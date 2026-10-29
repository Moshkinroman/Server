#pragma once
#include <string>

struct Params {
    int port = 33333;
    std::string dbPath = "/etc/vcalc.conf";
    std::string logPath = "/var/log/vcalc.log";
    bool showHelp = false;
};

class CLI {
public:
    CLI() = default;
    
    bool parse(int argc, char* argv[]);
    Params getParams() const;
    std::string getDescription() const;
    
private:
    Params params;
};
