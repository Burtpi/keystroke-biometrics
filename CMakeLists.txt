cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

project(KeystrokeBiometrics)
add_library(key_logger STATIC WootingSDK/key-logger.cpp)

add_executable(keystroke_biometrics main.cpp Logger/logger.cpp Utils/utils.cpp Config/config.cpp)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(keystroke_biometrics PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/libs/wooting_analog_sdk.lib")
target_link_libraries(keystroke_biometrics PRIVATE spdlog::spdlog_header_only)
target_link_libraries(keystroke_biometrics PRIVATE key_logger)