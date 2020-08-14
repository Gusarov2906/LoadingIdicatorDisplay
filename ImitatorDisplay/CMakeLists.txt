cmake_minimum_required(VERSION 3.5)

project(ImitatorDisplay LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



find_package(PkgConfig REQUIRED)
#find_package(SFML REQUIRED COMPONENTS graphics window system audio)
#set(SFML_LIBRARIES sfml-window sfml-graphics sfml-system sfml-audio)
pkg_check_modules(SFML REQUIRED sfml-all)

add_executable(ImitatorDisplay main.cpp)

target_include_directories(ImitatorDisplay PUBLIC ${SFML_INCLUDE_DIR})
target_compile_options(ImitatorDisplay PUBLIC ${SFML_CFLAGS_OTHER})
target_link_libraries(ImitatorDisplay PUBLIC ${SFML_LIBRARIES})
