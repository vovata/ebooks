cmake_minimum_required(VERSION 2.8)

aux_source_directory(. SRC_LIST)

project(chitanka)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include(CheckCXXCompilerFlag)
MESSAGE(STATUS "CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER} )

find_package(Threads)

set(Boost_FOUND FALSE)
set(BOOST_ROOT "/usr")
set(Boost_NO_BOOST_CMAKE OFF)
set(Boost_NO_SYSTEM_PATHS FALSE)
set(Boost_INCLUDE_DIR "-NOTFOUND")
find_package(Boost COMPONENTS REQUIRED program_options thread regex system filesystem serialization date_time iostreams log)

find_library(XML2_LIBRARY NAMES xml2)
find_path(XML2_INCLUDE_DIR NAMES libxml/xpath.h
                    PATHS /usr/include/libxml2)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")

find_package(CxxTest)

function(add_bool_option name default_value description)
    set (${name} ${default_value} CACHE BOOL "${description}")
    if (${name})
        add_definitions (-D${name})
    endif()
endfunction()

function(add_text_option name default_value description)
    #  message (${name} ${default_value} ${description})
    set(${name} ${default_value} CACHE STRING "${description}")
    add_definitions (-D${name}=${${name}})
endfunction()

function(add_compiler_flag_if_supported flag name)
  check_cxx_compiler_flag (${flag} ${name})
  if (${name})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}" PARENT_SCOPE)
  endif ()
endfunction()

function(add_compiler_release_flag_if_supported flag name)
  check_cxx_compiler_flag (${flag} ${name})
  if (${name})
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${flag}" PARENT_SCOPE)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${flag}" PARENT_SCOPE)
  endif ()
endfunction()


add_executable(hello
    main.cpp
)
