#include <config/config-manager.h>
#include <execute/execute.h>
#include <wooting_sdk/key-logger.h>

int main(int argc, char *argv[]) {
    bool argv_read = global_config_manager.ReadTerminalFlags(argc, argv);
    if (argv_read) {
        global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
            "Starting the program.");
        execute::Run();
        return EXIT_SUCCESS;
    } else {
        global_config_manager.GetLoggerConfig().GetGeneralLogger()->error(
            "Error while reading flags from the terminal.");
        return EXIT_FAILURE;
    }
}