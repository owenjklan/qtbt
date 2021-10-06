cmake_minimum_required(VERSION 3.20)
project(qtbt)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Bluetooth
        Gui
        Widgets
        REQUIRED)

add_executable(qtbt main.cpp qtbt.hpp qtbt.cpp)
target_link_libraries(qtbt
        Qt5::Core
        Qt5::Bluetooth
        Qt5::Gui
        Qt5::Widgets
        )

