cmake_minimum_required(VERSION 3.15)
project(ccp_planner
    VERSION 0.0.0
    DESCRIPTION "implementation of complete coverage path planning"
    LANGUAGES CXX)

find_package(Boost REQUIRED)
find_package(Eigen3 REQUIRED NO_MODULE)
find_package(glog  REQUIRED)

add_library(ccp_planner STATIC
    src/mode_base.cc
    src/contour_mode.cc
    src/zigzag_mode.cc
    src/complete_coverage_planner.cc)

target_compile_features(ccp_planner PRIVATE cxx_std_17)
target_include_directories(ccp_planner PUBLIC
    ${Boost_INCLUDE_DIR}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(ccp_planner
    PUBLIC Eigen3::Eigen
    PRIVATE glog::glog)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    enable_testing()
    add_subdirectory(tests)
endif ()
