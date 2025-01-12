cmake_minimum_required(VERSION 3.27)
project(OBDBluetoothScanner)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "D:/Apps/Qt/6.8.1/mingw_64/")
find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

include_directories("D:/Apps/Qt/6.8.1/mingw_64/include")
link_directories("D:/Apps/Qt/6.8.1/mingw_64/lib")

add_executable(OBDBluetoothScanner
    src/main.cpp
    src/BluetoothConnection.hpp
    src/BluetoothConnection.cpp
    src/OBD2Communication.hpp
    src/OBD2Communication.cpp
    src/BluetoothConnectionSimulator.cpp
    src/OBD2CommunicationSimulator.cpp
    src/BluetoothConnectionSimulator.hpp
    src/DTC_Codes.hpp
    src/MainWindow.hpp
    src/MainWindow.cpp
)

target_link_libraries(OBDBluetoothScanner PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core)

include(CPack)
