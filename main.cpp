#include <iostream>
#include "Logger/logger.h"
#include "wooting_sdk/key-logger.h"

int main(int argc, char *argv[])
{
    logger::InitLogger();
    wooting_sdk::KeyLogger logger1;
    while (true)
    {
        logger1.ReadFullBuffer();
    }
    return EXIT_SUCCESS;
}