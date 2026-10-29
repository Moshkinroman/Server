#include "ServerApp.h"
#include <iostream>

void ServerApp::run(int argc, char* argv[]) {
    // Разобрать параметры командной строки
    if (!cli.parse(argc, argv)) {
        std::cout << cli.getDescription();
        return;
    }
    
    Params params = cli.getParams();
    
    // Инициализировать логгер
    logger = std::make_unique<Logger>(params.logPath);
    
    // Загрузить базу данных
    try {
        authDB.load(params.dbPath);
        logger->logError("INFO", "Database loaded successfully");
    } catch (std::exception& e) {
        logger->logError("CRITICAL", std::string("Failed to load database: ") + e.what());
        throw;
    }
    
    // Запустить сервер
    try {
        networkServer.bind(params.port);
        logger->logError("INFO", "Server started on port " + std::to_string(params.port));
        
        // Главный цикл сервера
        while (true) {
            int clientSocket = networkServer.accept();
            logger->logError("INFO", "Client connected");
            
            // Обслужить клиента
            ClientSession session(clientSocket, authDB, *logger);
            session.handle();
            
            logger->logError("INFO", "Client disconnected");
        }
    } catch (std::exception& e) {
        logger->logError("CRITICAL", std::string("Server error: ") + e.what());
        throw;
    }
}
