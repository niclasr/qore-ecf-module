cmake_minimum_required(VERSION 3.0.0)

project(qore-lz4-module VERSION 0.0.1)

include(CheckCXXCompilerFlag)
include(GNUInstallDirs)

find_package(Qore REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LZ4 REQUIRED liblz4>=131)

check_cxx_compiler_flag(-fvisibility=hidden HAVE_GCC_VISIBILITY)

configure_file(${CMAKE_SOURCE_DIR}/cmake/config.h.cmake config.h)

set(CPP_SRC src/qore_lz4frame.cpp src/lz4_module.cpp)
set(QPP_SRC src/ql_lz4.qpp)
set(module_name "lz4")

qore_wrap_qpp(QPP_CPP_SRC ${QPP_SRC})

add_library(${module_name} SHARED ${CPP_SRC} ${QPP_CPP_SRC})
target_include_directories(${module_name} PUBLIC ${CMAKE_SOURCE_DIR}/src ${LZ4_INCLUDE_DIRS})

qore_binary_module(${module_name} "${PROJECT_VERSION}" ${LZ4_LDFLAGS})

install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_FULL_DOCDIR})

qore_dist("${PROJECT_VERSION}")
