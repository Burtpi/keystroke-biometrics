#include <iostream>
#include "Logger/logger.h"
#include "WootingSDK/key-logger.h"

int main(int argc, char *argv[])
{
    logger::InitLogger();
    wooting_sdk::KeyLogger logger1;
    return EXIT_SUCCESS;
}