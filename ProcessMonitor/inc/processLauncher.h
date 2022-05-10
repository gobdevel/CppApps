#ifndef __PROCESS_LAUNCHER_H__
#define __PROCESS_LAUNCHER_H__
#include "appConfig.h"

namespace ProcessMonitor {

class ProcessLauncher {
public:
    int launch(const AppConfig& cfg);
};

}  // namespace ProcessMonitor
#endif
