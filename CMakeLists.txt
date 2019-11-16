cmake_minimum_required(VERSION 3.7)

project(tlc59711)

find_package(pybind11 REQUIRED)
include_directories(${pybind11_INCLUDE_DIRS})
include_directories(include)

add_executable(demo src/main.cpp src/tlc59711.cpp)
target_link_libraries(demo bcm2835)

add_library(tlc59711 SHARED include/tlc59711.h src/tlc59711.cpp)
target_link_libraries(tlc59711 bcm2835)

pybind11_add_module(tlc59711-python src/tlc59711.cpp src/bindings.cpp)
target_link_libraries(tlc59711-python bcm2835)

include(GNUInstallDirs)
install(TARGETS tlc59711 DESTINATION "${CMAKE_INSTALL_LIBDIR}")
