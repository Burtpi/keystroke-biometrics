#include <config/config-manager.h>
#include <execute/execute.h>
#include <wooting_sdk/key-logger.h>

#include <iostream>

int main(int argc, char *argv[]) {
    bool argv_read = global_config_manager.ReadTerminalFlags(argc, argv);
    if (argv_read) {
        execute::Run();
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}