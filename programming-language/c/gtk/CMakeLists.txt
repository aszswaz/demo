cmake_minimum_required(VERSION 3.22.2)
project(gtk-demo)

message(STATUS "cmake binary directory: ${CMAKE_BINARY_DIR}")

# Compile commands are output to "compile_commands.json", so that tools such as "ccls" can provide assistance.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Set gcc compile options.
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g3 -ggdb")
set(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -Wall -g3 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -O3 -Wall")

add_executable(
    ${PROJECT_NAME}
    hello-world.c
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)
include_directories(${GTK_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GTK_LIBRARIES})
