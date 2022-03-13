cmake_minimum_required(VERSION 3.21)
project(sway_win_extra)

set(CMAKE_CXX_STANDARD 23)

include(GNUInstallDirs)

find_package(swayipc_cpp 1.0.0 REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} main.cpp client.h util.h env.h util.h)

target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        PRIVATE
        swayipc_cpp::swayipc_cpp
)

install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
