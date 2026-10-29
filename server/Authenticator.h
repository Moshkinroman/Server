#pragma once
#include <string>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>

class Authenticator {
public:
    Authenticator() = default;
    
    std::string generateSalt();
    bool verifySHA224(const std::string& password, 
                      const std::string& salt, 
                      const std::string& receivedHash);
    
private:
    std::string computeHash(const std::string& salt, const std::string& password);
};
