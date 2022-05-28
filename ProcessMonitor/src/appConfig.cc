#include "appConfig.h"

#include <fstream>
#include <sstream>
#include <string>

namespace ProcessMonitor {

Args AppConfigParser::parseArgs(const std::string& input) {
    Args result;
    Arg  arg;
    if (input.empty()) return result;

    std::stringstream ss(input);
    while (std::getline(ss, arg, ' ')) {
        result.emplace_back(std::move(arg));
    }
    return result;
}

AppConfig AppConfigParser::parseLine(const std::string& line) {
    std::vector<std::string> tokens;
    std::string              token;
    std::stringstream        ss(line);
    while (std::getline(ss, token, ';')) {
        tokens.emplace_back(std::move(token));
    }
    if (tokens.size() != 3) {
        throw std::runtime_error("Config error !!!");
    }

    Args args = parseArgs(tokens[1]);
    return AppConfig(std::move(tokens[0]), std::move(args),
                     (tokens[2][0] == '1' ? true : false));
}

AppConfigs AppConfigParser::parse(const std::string filename) {
    AppConfigs apps;
    if (filename.empty()) {
        throw std::runtime_error("Config file not present !!!");
        return apps;
    }

    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Could not open config file");

    std::string line;

    if (file.good()) {
        while (std::getline(file, line)) {
            apps.emplace_back(parseLine(line));
        }
    }
    return apps;
}
}  // namespace ProcessMonitor
