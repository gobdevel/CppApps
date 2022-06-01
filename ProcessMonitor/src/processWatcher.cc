#include "processWatcher.h"

#include "log.h"

using namespace Utils;

namespace ProcessMonitor {

void ProcessWatcher::watch(ProcessStatusCb f) {
    int status = 0, pid = 0;

    while ((pid = wait(&status)) > 0) {
        if (WIFEXITED(status)) {
            // Child process exited
            LOG(Log::Debug, "Pid : %u exited, signal %u ", pid,
                WTERMSIG(status));
            f(pid);
        }
        if (WIFSIGNALED(status)) {
            // Child process signaled sigkill
            LOG(Log::Debug, "Pid : %u signaled, signal %u ", pid,
                WTERMSIG(status));
            f(pid);
        }
    }
}

}  // namespace ProcessMonitor
