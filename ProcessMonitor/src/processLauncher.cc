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
            auto& args = cfg.getArgs();
            auto  size = args.size();
            // Create array of char*
            char** argv = (char**)malloc(sizeof(char*) * (size + 1));
            argv[size]  = NULL;
            for (int i = 0; i < size; ++i) {
                argv[i] = const_cast<char*>(args[i].c_str());
            }

            // Child process will keep on running forever
            execv(cfg.getApp().c_str(), argv);
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
