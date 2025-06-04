set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB SOURCES src/*.cpp src/*.h)

add_executable(${PROJECT_NAME}-server)
target_sources(${PROJECT_NAME}-server PRIVATE ${SOURCES})

target_link_libraries(${PROJECT_NAME}-server
    Qt6::Core
    Qt6::Network
)