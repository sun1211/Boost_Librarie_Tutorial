# Defines AppBase library target.
project(recipe_01)
cmake_minimum_required(VERSION 3.5)

include(GNUInstallDirs)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
set(Boost_USE_STATIC_LIBS ON)


# The complete cmake for using threads in linux systems must contain following commands
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

if(CMAKE_CXX_STANDARD EQUAL 98 OR CMAKE_CXX_STANDARD LESS 14)
   message(FATAL_ERROR "app requires c++14 or newer")
elseif(NOT CMAKE_CXX_STANDARD)
   set(CMAKE_CXX_STANDARD 14)
   set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

find_package(Boost 1.60 REQUIRED COMPONENTS system filesystem)

add_executable(main main.cpp)

target_link_libraries(main Boost::system Boost::filesystem rt)