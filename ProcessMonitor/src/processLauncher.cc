#include "processLauncher.h"

#include <sys/stat.h>
#include <unistd.h>

#include <future>
#include <thread>

#include "appConfig.h"
#include "log.h"

namespace ProcessMonitor {

using namespace Utils;

static char** getArgsPtr(const AppConfig& cfg) {
    char** argv = nullptr;
    auto&  args = cfg.getArgs();
    auto   size = args.size() + 2;
    // Create array of char*
    argv           = (char**)malloc(sizeof(char**) * (size));
    argv[size - 1] = NULL;
    argv[0]        = const_cast<char*>(cfg.getApp().c_str());
    for (int i = 1; i < size - 1; ++i) {
        argv[i] = const_cast<char*>(args[i - 1].c_str());
    }
    return argv;
}

static void demonise(char* argv[]) {
    // Change the file mode mask
    umask(0);

    // Open any log files here

    // Create a new sid for child process
    int sid = setsid();
    if (sid < 0) {
        LOG(Log::Emerg, "Set sid failure");
        assert(false);
    }

    // Change the current working directory
    //    if ((chdir("/")) < 0) {
    //        throw std::runtime_error("change directory error");
    //    }

    // Close all open file descriptors
    for (auto fd = sysconf(_SC_OPEN_MAX); fd > 0; --fd) {
        close(fd);
    }

    int ret = execv(argv[0], argv);
    if (ret < 0) {
        LOG(Log::Emerg, "Unable to execv : %s ", argv[0]);
    }
    exit(ret);
}

static int spawn(const AppConfig& cfg) {
    int pid = 0;

    pid = fork();
    if (pid < 0) {
        LOG(Log::Emerg, "Fork failure");
        assert(false);
    } else if (pid == 0) {
        demonise(getArgsPtr(cfg));
    }
    return pid;
}

int ProcessLauncher::launch(const AppConfig& cfg) {
    auto fut = std::async(spawn, std::ref(cfg));
    // wait for launch to complete.
    auto pid = fut.get();
    return pid;
}

}  // namespace ProcessMonitor
