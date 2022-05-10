#ifndef __PROCESS_WATCHER_H__
#define __PROCESS_WATCHER_H__
#include <functional>

namespace ProcessMonitor {

using ProcessStatusCb = std::function<void(int)>;

class ProcessWatcher {
public:
    void watch(ProcessStatusCb f);
};
}  // namespace ProcessMonitor
#endif
