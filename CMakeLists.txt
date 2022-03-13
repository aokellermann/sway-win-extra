cmake_minimum_required(VERSION 3.21)
project(sway_win_extra)

set(CMAKE_CXX_STANDARD 23)

find_package(swayipc_cpp 1.0.0 REQUIRED)
find_package(Threads REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        PRIVATE
        swayipc_cpp::swayipc_cpp_static
)
