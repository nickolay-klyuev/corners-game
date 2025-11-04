cmake_minimum_required(VERSION 4.0)

project(corners LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/sfml)

file(GLOB_RECURSE PRIVATE_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/private/*.cpp")
file(GLOB_RECURSE PUBLIC_HEADERS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/public/*.h" "src/public/*.hpp")

add_executable(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${PRIVATE_SOURCES}
    ${PUBLIC_HEADERS}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        "${CMAKE_SOURCE_DIR}/src/public"
        "${CMAKE_BINARY_DIR}"
)

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})