#include "AuthDB.h"

void AuthDB::load(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open database file: " + filePath);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string login = line.substr(0, pos);
            std::string password = line.substr(pos + 1);
            users[login] = password;
        }
    }
}

std::string AuthDB::getPassword(const std::string& login) const {
    auto it = users.find(login);
    if (it != users.end()) {
        return it->second;
    }
    throw std::runtime_error("Login not found: " + login);
}

bool AuthDB::hasLogin(const std::string& login) const {
    return users.find(login) != users.end();
}
