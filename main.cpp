#include <iostream>
#include <logger/logger.h>
#include <wooting_sdk/key-logger.h>
#include <execute/execute.h>

int main(int argc, char *argv[])
{
    logger::InitLogger();
    execute::Run();
    return EXIT_SUCCESS;
}