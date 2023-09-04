cmake_minimum_required(VERSION 3.16.3)

project(my-clang-diff)

if(NOT DEFINED CMAKE_PREFIX_PATH)
  message(FATAL_ERROR "Set CMAKE_PREFIX_PATH with -DCMAKE_PREFIX_PATH")
endif()

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

# set(CLANG_LINK_CLANG_DYLIB ${LLVM_LINK_LLVM_DYLIB})

list(APPEND CMAKE_MODULE_PATH ${LLVM_DIR})
include(AddLLVM)

set(CLANG_DIR ${CMAKE_PREFIX_PATH}/clang)
list(APPEND CMAKE_MODULE_PATH ${CLANG_DIR})
include(AddClang)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})

add_subdirectory(src)

