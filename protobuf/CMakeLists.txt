file(GLOB_RECURSE PROTOBUF_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")

add_library(protocol)
target_sources(protocol PRIVATE ${PROTOBUF_FILES})

target_include_directories(protocol
    PUBLIC
    ${Protobuf_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(protocol
    PUBLIC
    ${Protobuf_LIBRARIES})

protobuf_generate(TARGET protocol LANGUAGE cpp)
