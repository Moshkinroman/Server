#include "CLI.h"
#include <cstring>
#include <sstream>

bool CLI::parse(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            params.showHelp = true;
            return false;
        }
        else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0) {
            if (i + 1 < argc) {
                params.port = std::stoi(argv[++i]);
            }
        }
        else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--db") == 0) {
            if (i + 1 < argc) {
                params.dbPath = argv[++i];
            }
        }
        else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--log") == 0) {
            if (i + 1 < argc) {
                params.logPath = argv[++i];
            }
        }
    }
    return true;
}

Params CLI::getParams() const {
    return params;
}

std::string CLI::getDescription() const {
    std::ostringstream ss;
    ss << "Server options:\n"
       << "  -h, --help     Show help\n"
       << "  -p, --port     Server port (default: 33333)\n"
       << "  -d, --db       Database file (default: /etc/vcalc.conf)\n"
       << "  -l, --log      Log file (default: /var/log/vcalc.log)\n";
    return ss.str();
}
