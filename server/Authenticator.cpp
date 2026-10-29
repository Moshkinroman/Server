#include "Authenticator.h"
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>


std::string Authenticator::generateSalt() {
    CryptoPP::byte salt[8]; // 64 бита = 8 байт
    CryptoPP::AutoSeededRandomPool prng;
    prng.GenerateBlock(salt, sizeof(salt));
    
    std::string saltHex;
    CryptoPP::StringSource(salt, sizeof(salt), true,
        new CryptoPP::HexEncoder(
            new CryptoPP::StringSink(saltHex)));
    
    // Дополнить нулями слева до 16 символов
    while (saltHex.length() < 16) {
        saltHex = "0" + saltHex;
    }
    
    return saltHex;
}

bool Authenticator::verifySHA224(const std::string& password, 
                                  const std::string& salt, 
                                  const std::string& receivedHash) {
    std::string expectedHash = computeHash(salt, password);
    return expectedHash == receivedHash;
}

std::string Authenticator::computeHash(const std::string& salt, const std::string& password) {
    std::string data = salt + password;
    std::string hash;
    
    CryptoPP::SHA224 sha224;
    CryptoPP::StringSource(data, true,
        new CryptoPP::HashFilter(sha224,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(hash))));
    
    return hash;
}
