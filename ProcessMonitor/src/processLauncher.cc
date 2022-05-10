#include "processLauncher.h"

#include <unistd.h>

#include <future>

namespace ProcessMonitor {

static int spawn(const AppConfig& cfg) {
    int pid = 0;
    switch (pid = fork()) {
        case -1: {
            throw std::runtime_error("Fork failure !!!");
        } break;
        case 0: {
            char* newArgv[] = {NULL};
            char* newEnv[]  = {NULL};

            // Child process will keep on running forever
            execv(cfg.getApp().c_str(), newArgv);
        } break;
        default:
            break;
    }

    // Child process pid
    return pid;
}

int ProcessLauncher::launch(const AppConfig& cfg) {
    auto fut = std::async(spawn, cfg);
    // wait for launch to complete.
    auto pid = fut.get();
    return pid;
}

#if 0
int ProcessLauncher::launch(const AppConfig& cfg) {}

}
#endif
}  // namespace ProcessMonitor
