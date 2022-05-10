#ifndef __PROCESS_INFO_H__
#define __PROCESS_INFO_H__
#include "appConfig.h"

namespace ProcessMonitor {

class ProcessInfo {
public:
    explicit ProcessInfo(AppConfig appConfig, int pid)
        : m_configs(std::move(appConfig)), m_pid(pid) {}

    int              getPid() const noexcept { return m_pid; }
    const AppConfig& getConfig() const noexcept { return m_configs; }
    AppConfig&       getConfig() noexcept { return m_configs; }

private:
    AppConfig m_configs;
    int       m_pid;
};

}  // namespace ProcessMonitor

#endif
