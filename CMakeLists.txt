cmake_minimum_required(VERSION 3.27)
project(OBDBluetoothScanner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

list(APPEND CMAKE_PREFIX_PATH "D:\\Programy\\Qt\\6.7.1\\mingw_64\\lib\\cmake")

find_package(Qt6 COMPONENTS Widgets REQUIRED)

qt6_wrap_cpp(MOC_FILES src/main.cpp)

add_executable(OBDBluetoothScanner src/main.cpp
        ${MOC_FILES}
        src/BluetoothConnection.h
        src/BluetoothConnection.cpp
        src/OBD2Communication.h
        src/OBD2Communication.cpp
        src/BluetoothConnectionSimulator.cpp
        src/OBD2CommunicationSimulator.cpp
        src/BluetoothConnectionSimulator.h
        src/DTC_Codes.h
        src/MainWindow.h
        src/MainWindow.cpp)

target_link_libraries(OBDBluetoothScanner ws2_32 Qt6::Widgets)