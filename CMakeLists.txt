cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

project(KeystrokeBiometrics)
add_library(key_logger STATIC wooting_sdk/key-logger.cpp)
add_library(execute STATIC execute/execute.cpp execute/external/execute-external.cpp execute/logger/execute-logger.cpp)
add_library(utils STATIC utils/time/utils-time.cpp utils/key/utils-key.cpp utils/key/validators/utils-key-validators.cpp)
add_library(config STATIC config/config-manager.cpp config/app-config.cpp config/language-config.cpp config/calc-config.cpp)
add_library(logger STATIC logger/logger.cpp)
add_library(database STATIC database/database.cpp database/models/key-hit.cpp database/models/ngraph.cpp database/containers/key-hit-container.cpp database/containers/ngraph-container.cpp)

add_executable(keystroke_biometrics main.cpp)

target_include_directories(keystroke_biometrics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(spdlog CONFIG REQUIRED)
find_package(GSL REQUIRED)

target_link_libraries(keystroke_biometrics PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/libs/wooting_analog_sdk.lib")
target_link_libraries(keystroke_biometrics PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/libs/libfftw3f-3.lib")
target_link_libraries(keystroke_biometrics PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/libs/libfftw3l-3.lib")
target_link_libraries(keystroke_biometrics PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/libs/libfftw3-3.lib")

target_link_libraries(keystroke_biometrics PRIVATE spdlog::spdlog_header_only GSL::gsl GSL::gslcblas)
target_link_libraries(keystroke_biometrics PRIVATE key_logger execute utils config logger database)