#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

#include <ostream>
#include <string>
#include <tuple>
#include <vector>

namespace ProcessMonitor {

using Arg  = std::string;
using Args = std::vector<Arg>;

class AppConfig {
public:
    AppConfig(std::string app, Args args, bool restart)
        : m_app(std::move(app)), m_args(std::move(args)), m_restart(restart) {}

    std::string getApp() const noexcept { return m_app; }
    const Args& getArgs() const noexcept { return m_args; }
    bool        isRestartable() const noexcept { return m_restart; }

    friend bool operator==(const AppConfig& lhs, const AppConfig& rhs) {
        return std::tie(lhs.m_app, lhs.m_args, lhs.m_restart) ==
               std::tie(rhs.m_app, rhs.m_args, rhs.m_restart);
    }

    friend bool operator!=(const AppConfig& lhs, const AppConfig& rhs) {
        return std::tie(lhs.m_app, lhs.m_args, lhs.m_restart) !=
               std::tie(rhs.m_app, rhs.m_args, rhs.m_restart);
    }

    friend std::ostream& operator<<(std::ostream&    stream,
                                    const AppConfig& obj) {
        stream << obj.m_app;
        for (auto& arg : obj.m_args) {
            stream << ", " << arg;
        }

        stream << ", " << obj.m_restart;
        return stream;
    }

private:
    std::string m_app;
    Args        m_args;
    bool        m_restart;
};

using AppConfigs = std::vector<AppConfig>;

class AppConfigParser {
public:
    static AppConfigs parse(const std::string filename);
    static Args       parseArgs(const std::string& input);
    static AppConfig  parseLine(const std::string& line);
};

}  // namespace ProcessMonitor
#endif
