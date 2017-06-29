cmake_minimum_required(VERSION 3.3.0)

project(qore-lz4-module VERSION 0.0.1)

include(CheckCXXCompilerFlag)
include(GNUInstallDirs)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(Qore 0.8.12 REQUIRED)
find_package(LZ4F 100 REQUIRED)

check_cxx_compiler_flag(-fvisibility=hidden HAVE_GCC_VISIBILITY)

configure_file(${CMAKE_SOURCE_DIR}/cmake/config.h.cmake config.h)

set(CPP_SRC src/qore_lz4frame.cpp src/lz4_module.cpp)
set(QPP_SRC src/ql_lz4.qpp)
set(module_name "lz4")

qore_wrap_qpp(QPP_CPP_SRC ${QPP_SRC})

add_library(${module_name} SHARED ${CPP_SRC} ${QPP_CPP_SRC})
target_include_directories(${module_name} PUBLIC ${CMAKE_SOURCE_DIR}/src ${LZ4F_INCLUDE_DIR})

# qore version 0.8.13 and above requires c++11
if ((Qore_VERSION VERSION_GREATER "0.8.13") OR (Qore_VERSION VERSION_EQUAL "0.8.13"))
set_target_properties(${module_name} PROPERTIES
                      CXX_STANDARD 11
                      CXX_STANDARD_REQUIRED ON
                      CXX_EXTENSIONS OFF)
endif()

qore_binary_module(${module_name} "${PROJECT_VERSION}" ${LZ4_LIB})

install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_FULL_DOCDIR})

qore_dist("${PROJECT_VERSION}")
