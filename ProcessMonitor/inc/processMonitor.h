#ifndef __PROCESS_MONITOR_H__
#define __PROCESS_MONITOR_H__

#include <unordered_map>

#include "appConfig.h"
#include "processInfo.h"
#include "processLauncher.h"
#include "processWatcher.h"

namespace ProcessMonitor {

using ProcessInfos = std::unordered_map<int, ProcessInfo>;

class ProcessMonitor {
public:
    void start();
    void restart(int pid);

private:
    ProcessInfos    m_processInfos;
    ProcessLauncher m_launcher;
    ProcessWatcher  m_watcher;
};
}  // namespace ProcessMonitor
#endif
