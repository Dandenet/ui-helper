cmake_minimum_required(VERSION 3.22)
project(halper-ui)

find_package(Qt6 COMPONENTS Core Gui Widgets Network Qml)
find_package(Protobuf REQUIRED)

add_subdirectory(ui)
add_subdirectory(protobuf)
add_subdirectory(server)