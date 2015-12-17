# Copyright (c) 2013-2014 vovata@gmail.com

# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:

# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

cmake_minimum_required(VERSION 3.0.2)

aux_source_directory(. SRC_LIST)

project(chitanka)

# standart packages
find_package(Threads)

# additional packages
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(SetCompiler)
include(SetBoost)
include(SetOptions)
#include(SetXml2)
#include(SetCxxTest)

include_directories(
    ./
)

add_executable(showhello
    tests/showhello.cpp
)

target_link_libraries(showhello
    logging
)

add_library(logging SHARED
    logging/loggingwriter.cpp
    logging/severitychannel.cpp
    logging/logsource.cpp
    logging/coreutil.cpp
)

target_link_libraries(logging
    ${Boost_LIBRARIES}
)

set_property(TARGET logging PROPERTY POSITION_INDEPENDENT_CODE TRUE)

if(${USE_PRECOMPILED})
    add_precompiled_header(logging common/precompiled.hpp)
endif()

add_library(options SHARED
    options/options.cpp
)

target_link_libraries(options
    ${Boost_LIBRARIES}
)

set_property(TARGET options PROPERTY POSITION_INDEPENDENT_CODE TRUE)

if(${USE_PRECOMPILED})
    add_precompiled_header(options common/precompiled.hpp)
endif()

add_executable(showoptions
    tests/showoptions.cpp
)

target_link_libraries(showoptions
    options
    logging
)

include(DefCustomTargets)
