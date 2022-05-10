#include "processWatcher.h"

#include <iostream>

namespace ProcessMonitor {

void ProcessWatcher::watch(ProcessStatusCb f) {
    int status = 0, pid = 0;

    while ((pid = waitpid(0, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            // Child process exited
            std::cout << "Pid : " << pid << " exited !!!\n";
            f(pid);
        }
        if (WIFSIGNALED(status)) {
            // Child process signaled sigkill
            std::cout << "Pid : " << pid << " signaled !!!\n";
            f(pid);
        }
    }
}

}  // namespace ProcessMonitor
