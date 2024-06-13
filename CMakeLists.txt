cmake_minimum_required(VERSION 3.27)
project(OBDBluetoothScanner)

set(CMAKE_CXX_STANDARD 17)

add_executable(OBDBluetoothScanner src/main.cpp
        src/BluetoothConnection.h
        src/BluetoothConnection.cpp
        src/OBD2Communication.h
        src/OBD2Communication.cpp)

target_link_libraries(OBDBluetoothScanner ws2_32)