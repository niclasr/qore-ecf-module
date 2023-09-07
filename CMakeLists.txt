cmake_minimum_required(VERSION 3.6.0)

project(qore-ecf-module VERSION 0.0.1)

include(CheckCXXCompilerFlag)
include(GNUInstallDirs)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(Qore 1.12.14 REQUIRED)
find_package(LZ4F 100 REQUIRED)
find_package(Snappy 1.1.4 REQUIRED)

check_cxx_compiler_flag(-fvisibility=hidden HAVE_GCC_VISIBILITY)

configure_file(${CMAKE_SOURCE_DIR}/cmake/config.h.cmake config.h)

set(CPP_SRC
    src/binarynode_sink.cpp 
    src/ecf_module.cpp
    src/qore_lz4frame.cpp
    src/qore_snappy.cpp)


set(QPP_SRC src/ql_ecf.qpp)
set(module_name "ecf")

qore_wrap_qpp_value(QPP_CPP_SRC ${QPP_SRC})

add_library(${module_name} SHARED ${CPP_SRC} ${QPP_CPP_SRC})
target_include_directories(${module_name} PUBLIC
                           ${CMAKE_SOURCE_DIR}/src)

# qore requires c++11
set_target_properties(${module_name} PROPERTIES
                      CXX_STANDARD 11
                      CXX_STANDARD_REQUIRED ON
                      CXX_EXTENSIONS OFF)

qore_binary_module(${module_name}
                   "${PROJECT_VERSION}"
                   LZ4F::LZ4F
                   Snappy::snappy)

install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_FULL_DOCDIR})

qore_dist("${PROJECT_VERSION}")
