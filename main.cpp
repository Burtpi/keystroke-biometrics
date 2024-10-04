#include <execute/execute.h>
#include <logger/logger.h>
#include <wooting_sdk/key-logger.h>

#include <iostream>

int main(int argc, char *argv[]) {
    logger::InitLogger();
    execute::Run();
    return EXIT_SUCCESS;
}