#pragma once
#include <string>
#include <map>
#include <fstream>
#include <stdexcept>

class AuthDB {
public:
    AuthDB() = default;
    
    void load(const std::string& filePath);
    std::string getPassword(const std::string& login) const;
    bool hasLogin(const std::string& login) const;
    
private:
    std::map<std::string, std::string> users;
};
