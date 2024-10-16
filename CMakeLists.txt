cmake_minimum_required(VERSION 3.27)
project(training-boost-asio)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
fetchcontent_declare(
    Boost
    GIT_REPOSITORY "https://github.com/boostorg/boost.git"
    GIT_TAG "boost-1.86.0"
    GIT_PROGRESS ON
    GIT_SHALLOW ON
    OVERRIDE_FIND_PACKAGE TRUE # needed to find correct Boost
    EXCLUDE_FROM_ALL # compile only what you need
)
fetchcontent_makeavailable(Boost)

find_package(
    Boost
    1.86.0
    EXACT
    REQUIRED
    COMPONENTS asio
)

add_executable(silly-server-exe silly_server.cpp)
add_executable(silly-client-exe silly_client.cpp)

target_link_libraries(silly-client-exe PRIVATE Boost::asio)
target_link_libraries(silly-server-exe PRIVATE Boost::asio)
