#include <filesystem>
#include <functional>
#include <iostream>
#include <tuple>
#include <utility>

#include "processMonitor.h"

const std::string g_configFilename{"testConfig.txt"};

namespace ProcessMonitor {

void ProcessMonitor::start() {
    auto configs = AppConfigParser::parse(g_configFilename);

    for (auto& cfg : configs) {
        if (std::filesystem::exists(cfg.getApp())) {
            auto app = cfg.getApp();
            auto pid = m_launcher.launch(cfg);

            //        m_processInfos.emplace(
            //            std::make_pair(pid, ProcessInfo(std::move(cfg),
            //            pid)));
            if (pid != 0) {
                m_processInfos.emplace(
                    std::piecewise_construct, std::forward_as_tuple(pid),
                    std::forward_as_tuple(std::move(cfg), pid));

                std::cout << "Launched App : " << app << ", pid : " << pid
                          << "\n";
            }
        }
    }
    m_watcher.watch(
        std::bind(&ProcessMonitor::restart, &(*this), std::placeholders::_1));
}

void ProcessMonitor::restart(int pid) {
    auto it = m_processInfos.find(pid);
    if (it == m_processInfos.end()) {
        // TODO ERROR
        std::cout << "Restart : Unable to find pid : " << pid << "\n";
        return;
    }
    auto cfg = std::move(it->second.getConfig());
    std::cout << "Re Launching App : " << cfg.getApp() << "\n";

    m_processInfos.erase(it);
    auto newPid = m_launcher.launch(cfg);
    m_processInfos.emplace(std::piecewise_construct,
                           std::forward_as_tuple(newPid),
                           std::forward_as_tuple(std::move(cfg), newPid));
}
}  // namespace ProcessMonitor
