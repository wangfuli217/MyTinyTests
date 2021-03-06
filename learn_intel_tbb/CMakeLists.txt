
# CMake 最低版本要求
cmake_minimum_required (VERSION 3.8)

# compile toolchain (should set before `project()`)
if (UNIX)
message("UNIX-like OS")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER "gcc")
endif(UNIX)
if (WIN32)
message("Windows")
set(CMAKE_GENERATOR "Visual Studio 14 2015 Win64")
message("Expect to use: " ${CMAKE_GENERATOR})
endif(WIN32)

if (NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE "Debug")
endif()
message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

# project basic information
project (learn_intel_tbb)

# compile options, should set after `project()`, otherwise it won't work
if (UNIX)
set(CMAKE_CXX_FLAGS "$ENV{CMAKE_CXX_FLAGS} -std=c++11") # also coult replace with `add_compile_options(-std=c++11)`
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG -DTBB_USE_DEBUG=1")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -UDEBUG")
endif(UNIX)
if (WIN32)
add_compile_options("/MP")  #multi-processor compile
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D \"DEBUG\" /D \"_DEBUG=1\"")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
endif(WIN32)
message("CMAKE_CXX_FLAGS " is ${CMAKE_CXX_FLAGS})
message("CMAKE_CXX_FLAGS_DEBUG " is ${CMAKE_CXX_FLAGS_DEBUG})
message("CMAKE_CXX_FLAGS_RELEASE " is ${CMAKE_CXX_FLAGS_RELEASE})

# include/link directories for tbb
include_directories(${PROJECT_SOURCE_DIR}/modules/tbb2019_20181010oss/include/)
link_directories(${PROJECT_SOURCE_DIR}/modules/tbb2019_20181010oss/lib/intel64/gcc4.7/)

# find source files automatically, then set to var DIR_SRCS
#aux_source_directory(src DIR_SRCS)

set(SRC_PATH src)

# target
set(PARALLEL_FOR_TEST_TARGET parallel_for_test)
add_executable (${PARALLEL_FOR_TEST_TARGET} ${SRC_PATH}/${PARALLEL_FOR_TEST_TARGET}.cc)

set(PARALLEL_REDUCE_TEST_TARGET parallel_reduce_test)
add_executable (${PARALLEL_REDUCE_TEST_TARGET} ${SRC_PATH}/${PARALLEL_REDUCE_TEST_TARGET}.cc)

set(PARALLEL_DO_TEST_TARGET parallel_do_test)
add_executable (${PARALLEL_DO_TEST_TARGET} ${SRC_PATH}/${PARALLEL_DO_TEST_TARGET}.cc)


# link lib in subfolder
if (UNIX)
target_link_libraries(${PARALLEL_FOR_TEST_TARGET} 
    debug libtbb_debug.so 
    #debug libtbb_preview_debug.so
    #debug libtbbmalloc_debug.so
    #debug libtbbmalloc_proxy_debug.so

    optimized libtbb.so 
    #optimized libtbb_preview.so
    #optimized libtbbmalloc.so
    #optimized libtbbmalloc_proxy.so
)

target_link_libraries(${PARALLEL_REDUCE_TEST_TARGET} 
    debug libtbb_debug.so 
    #debug libtbb_preview_debug.so
    #debug libtbbmalloc_debug.so
    #debug libtbbmalloc_proxy_debug.so

    optimized libtbb.so 
    #optimized libtbb_preview.so
    #optimized libtbbmalloc.so
    #optimized libtbbmalloc_proxy.so
)

target_link_libraries(${PARALLEL_DO_TEST_TARGET} 
    debug libtbb_debug.so 
    #debug libtbb_preview_debug.so
    #debug libtbbmalloc_debug.so
    #debug libtbbmalloc_proxy_debug.so

    optimized libtbb.so 
    #optimized libtbb_preview.so
    #optimized libtbbmalloc.so
    #optimized libtbbmalloc_proxy.so
)


endif(UNIX)
