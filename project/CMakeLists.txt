cmake_minimum_required(VERSION 3.21.0)
project(Dash_n_Dots VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(Dash_n_Dots main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
