#include "appConfig.h"

#include <fstream>
#include <sstream>
#include <string>

namespace ProcessMonitor {

AppConfigs AppConfigParser::parse(std::string filename) {
    AppConfigs apps;
    if (filename.empty()) {
        throw std::runtime_error("Config file not present !!!");
        return apps;
    }

    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Could not open config file");

    std::vector<std::string> tokens;
    std::string              line, token;

    if (file.good()) {
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            while (std::getline(ss, token, ';')) {
                tokens.emplace_back(std::move(token));
            }
            if (tokens.size() != 3) {
                throw std::runtime_error("Config error !!!");
            }
            apps.emplace_back(AppConfig(std::move(tokens[0]),
                                        std::move(tokens[1]),
                                        (tokens[2][0] == '1') ? true : false));
            tokens.clear();
        }
    }
    return apps;
}
}  // namespace ProcessMonitor
