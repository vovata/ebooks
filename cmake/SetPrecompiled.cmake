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

# precompiled
function(add_precompiled_header target precompiled_header)
    set(flags ${CMAKE_CXX_FLAGS})

    separate_arguments(flags UNIX_COMMAND ${flags})

    string(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" cmake_flags_name)
    if (${cmake_flags_name})
        separate_arguments(cmake_flags UNIX_COMMAND ${${cmake_flags_name}})
        list(APPEND flags ${cmake_flags})
    endif(${cmake_flags_name})

    get_target_property(compiler_flags ${target} COMPILE_FLAGS)
    if (${compiler_flags})
        list(APPEND flags ${compiler_flags})
    endif(${compiler_flags})

    get_directory_property(directory_flags INCLUDE_DIRECTORIES)
    foreach(item ${directory_flags})
        list(APPEND flags "-I${item}")
    endforeach(item)

    get_directory_property(directory_flags COMPILE_DEFINITIONS)
    foreach(item ${directory_flags})
        list(APPEND flags "-D${item}")
    endforeach(item)

    get_target_property(targetType ${target} TYPE)
    if(${targetType} STREQUAL SHARED_LIBRARY)
        list(APPEND flags -fPIC)
    endif()

    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/precompiled.gch/${target})

    get_filename_component(precompiled_file ${precompiled_header} NAME)
    if(${debug_cmake})
        message(STATUS "PRECOMPILED -- ${CMAKE_CXX_COMPILER} ${flags} ${precompiled_header} -o ${CMAKE_BINARY_DIR}/precompiled.gch/${target}/${precompiled_file}.gch")
    endif()

    add_custom_target(precompiled_${target} ALL
        DEPENDS precompiled.gch/${target}/${precompiled_file}.gch
    )

    add_custom_command(OUTPUT precompiled.gch/${target}/${precompiled_file}.gch
        COMMAND ${CMAKE_CXX_COMPILER} ${flags} ${CMAKE_CURRENT_SOURCE_DIR}/${precompiled_header} -o precompiled.gch/${target}/${precompiled_file}.gch
        MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${precompiled_header}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM
        COMMENT "Building precompiled header for ${target}"
    )

    add_dependencies(${target} precompiled_${target})

    set_target_properties(${target}
        PROPERTIES COMPILE_FLAGS " -include ${CMAKE_CURRENT_SOURCE_DIR}/${precompiled_header} -Winvalid-pch"
    )
endfunction()
