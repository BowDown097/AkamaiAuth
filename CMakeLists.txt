cmake_minimum_required(VERSION 3.0.0)
project(AkamaiAuth VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(AkamaiAuth akamaiauth.c akamaiauth.h main.c md5.c md5.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
