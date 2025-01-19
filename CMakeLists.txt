cmake_minimum_required(VERSION 3.27)
project(OBDBluetoothScanner)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DUSE_SIMULATED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "D:/Apps/Qt/6.8.1/mingw_64/")
find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core Quick QuickControls2 Qml)

include_directories("D:/Apps/Qt/6.8.1/mingw_64/include")
link_directories("D:/Apps/Qt/6.8.1/mingw_64/lib")

add_executable(OBDBluetoothScanner
        src/main.cpp
        src/resources.qrc
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
        src/ui/StartWindow.qml
        src/ui/ConnectedWindow.qml
        src/ui/ConnectingWindow.qml
        src/ui/Constants.qml
        src/sim/SimBluetoothConnection.hpp
        src/sim/SimBluetoothConnection.cpp
        src/interface/IBluetoothConnection.hpp
        src/interface/IOBD2Communication.hpp
        src/sim/SimOBD2Communication.cpp
        src/sim/SimOBD2Communication.hpp
)

target_link_libraries(OBDBluetoothScanner PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core Qt6::Quick Qt6::QuickControls2 Qt6::Qml)

include(CPack)