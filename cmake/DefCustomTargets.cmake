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

#this target helps the qt creator to find and parse all other files
file(GLOB_RECURSE target_SOURCE_HEADERS "*.h" "*.hpp")
list(APPEND SOURCE_HEADERS ${target_SOURCE_HEADERS})
file(GLOB_RECURSE target_SAMPLES "config/*.sample")
list(APPEND SAMPLES ${target_SAMPLES})
file(GLOB_RECURSE target_NOTES "notes/*.txt")
list(APPEND NOTES ${target_NOTES})
file(GLOB_RECURSE target_XSDS "xsd/*.xsd")
list(APPEND XSDS ${target_XSDS})

add_custom_target(source_headers SOURCES ${SOURCE_HEADERS} ${SAMPLES} ${NOTES} ${XSDS})
