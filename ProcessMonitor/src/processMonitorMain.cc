#include <filesystem>

#include "log.h"
#include "processMonitor.h"

const std::string g_configFilename{"testConfig.txt"};

using namespace Utils;

namespace ProcessMonitor {

void ProcessMonitor::start() {
    auto configs = AppConfigParser::parse(g_configFilename);

    for (auto& cfg : configs) {
        if (std::filesystem::exists(cfg.getApp())) {
            auto app = cfg.getApp();
            auto pid = m_launcher.launch(cfg);

            if (pid != 0) {
                m_processInfos.emplace(
                    std::piecewise_construct, std::forward_as_tuple(pid),
                    std::forward_as_tuple(std::move(cfg), pid));

                LOG(Log::Info, "Launched App : %s, pid %u ", app.c_str(), pid);
            }
        }
    }
    m_watcher.watch(
        std::bind(&ProcessMonitor::restart, &(*this), std::placeholders::_1));
}

void ProcessMonitor::restart(int pid) {
    auto it = m_processInfos.find(pid);
    if (it == m_processInfos.end()) {
        LOG(Log::Err, "Restart : Unable to find pid %u ", pid);
        return;
    }
    auto cfg = std::move(it->second.getConfig());

    m_processInfos.erase(it);
    if (cfg.isRestartable()) {
        LOG(Log::Info, "Re Launching App : %s, old pid %u ",
            cfg.getApp().c_str(), pid);
        auto newPid = m_launcher.launch(cfg);
        m_processInfos.emplace(std::piecewise_construct,
                               std::forward_as_tuple(newPid),
                               std::forward_as_tuple(std::move(cfg), newPid));
    }
}
}  // namespace ProcessMonitor
