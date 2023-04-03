cmake_minimum_required(VERSION 3.0.0)
project(lab1 VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB SOURCES "src/*.cpp")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS
    Core
    Widgets
    REQUIRED
    )

add_executable(lab1 ${SOURCES})
target_include_directories(lab1
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(lab1 Qt5::Core Qt5::Widgets)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
