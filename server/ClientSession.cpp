#include "ClientSession.h"
#include <cstring>
#include <stdexcept>
#include <unistd.h>
#include "Logger.h"

ClientSession::ClientSession(int clientSocket, AuthDB& authDB, Logger& logger)
    : clientSocket(clientSocket), authDB(authDB), logger(logger) {
}

ClientSession::~ClientSession() {
    if (clientSocket != -1) {
        ::close(clientSocket);
    }
}

void ClientSession::handle() {
    try {
        if (authenticate()) {
            processData();
        }
    } catch (std::exception& e) {
        logger.logError("ERROR", std::string("Client session error: ") + e.what());
    }
}

bool ClientSession::authenticate() {
    try {
        std::string login = recvString();
        
        if (!authDB.hasLogin(login)) {
            sendString("ERR");
            logger.logError("WARNING", "Login not found: " + login);
            return false;
        }
        
        std::string salt = authenticator.generateSalt();
        sendString(salt);
        
        std::string receivedHash = recvString();
        
        std::string password = authDB.getPassword(login);
        if (!authenticator.verifySHA224(password, salt, receivedHash)) {
            sendString("ERR");
            logger.logError("WARNING", "Invalid hash for login: " + login);
            return false;
        }
        
        sendString("OK");
        return true;
        
    } catch (std::exception& e) {
        logger.logError("ERROR", std::string("Authentication error: ") + e.what());
        return false;
    }
}

void ClientSession::processData() {
    try {
        while (true) {
            uint32_t vectorSize;
            recvData(&vectorSize, sizeof(vectorSize));
            
            if (vectorSize == 0) {
                break;
            }
            
            std::vector<float> values(vectorSize);
            recvData(values.data(), vectorSize * sizeof(float));
            
            float result = calculator.average(values);
            
            sendData(&result, sizeof(result));
        }
    } catch (std::exception& e) {
        logger.logError("ERROR", std::string("Data processing error: ") + e.what());
    }
}

void ClientSession::sendData(const void* data, size_t size) {
    ssize_t sent = send(clientSocket, data, size, 0);
    if (sent == -1) {
        throw std::runtime_error("Send failed");
    }
}

void ClientSession::recvData(void* data, size_t size) {
    ssize_t received = recv(clientSocket, data, size, 0);
    if (received == -1) {
        throw std::runtime_error("Recv failed");
    }
    if (static_cast<size_t>(received) != size) {
        throw std::runtime_error("Incomplete data received");
    }
}

void ClientSession::sendString(const std::string& str) {
    // Текстовый формат: строка + \n
    std::string message = str + "\n";
    sendData(message.c_str(), message.length());
}

std::string ClientSession::recvString() {
    // Текстовый формат: читаем байт за байтом до \n
    std::string result;
    char ch;
    while (true) {
        ssize_t rc = recv(clientSocket, &ch, 1, 0);
        if (rc <= 0) {
            throw std::runtime_error("Connection closed");
        }
        if (ch == '\n') {
            break;
        }
        result += ch;
    }
    return result;
}
