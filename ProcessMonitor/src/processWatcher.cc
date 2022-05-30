#include "processWatcher.h"

#include <iostream>

namespace ProcessMonitor {

void ProcessWatcher::watch(ProcessStatusCb f) {
    int status = 0, pid = 0;

    while ((pid = wait(&status)) > 0) {
        if (WIFEXITED(status)) {
            // Child process exited
            std::cout << "Pid : " << pid << " exited !!!\n";
            f(pid);
        }
        if (WIFSIGNALED(status)) {
            // Child process signaled sigkill
            std::cout << "Pid : " << pid << " signaled : " << WTERMSIG(status)
                      << "\n";
            f(pid);
        }
    }
}

}  // namespace ProcessMonitor
