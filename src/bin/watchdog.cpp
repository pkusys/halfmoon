#include "base/init.h"
#include "base/common.h"

#include "watchdog/watchdog.h"

#include <absl/flags/flag.h>

ABSL_FLAG(std::string, gateway_ipc_path, "/tmp/faas_gateway",
          "Domain socket path for IPC with the gateway process");
ABSL_FLAG(std::string, shared_mem_path, "/dev/shm/faas",
          "Root directory for shared memories used by FaaS");
ABSL_FLAG(std::string, func_config_file, "", "Path to function config file");
ABSL_FLAG(int, func_id, -1, "Function ID");
ABSL_FLAG(std::string, fprocess, "", "Function process");
ABSL_FLAG(int, run_mode, 1, "Function run mode");

int main(int argc, char* argv[]) {
    faas::base::InitMain(argc, argv);

    auto watchdog = absl::make_unique<faas::watchdog::Watchdog>();
    watchdog->set_gateway_ipc_path(absl::GetFlag(FLAGS_gateway_ipc_path));
    watchdog->set_func_id(absl::GetFlag(FLAGS_func_id));
    watchdog->set_fprocess(absl::GetFlag(FLAGS_fprocess));
    watchdog->set_shared_mem_path(absl::GetFlag(FLAGS_shared_mem_path));
    watchdog->set_run_mode(absl::GetFlag(FLAGS_run_mode));

    watchdog->Start();
    watchdog->WaitForFinish();

    return 0;
}