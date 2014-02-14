/*
 * Copyright (c) 2013-2014 vovata@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "loggerdefine.h"

#include <algorithm>

namespace common
{

logging_severity_type get_max_logging_severity_value()
{
    static logging_severity_type max_severity_value = 0;

    if (max_severity_value == 0)
    {
        max_severity_value = std::max(max_severity_value, static_cast<logging_severity_type>(logging_severity::trace));
        max_severity_value = std::max(max_severity_value, static_cast<logging_severity_type>(logging_severity::debug));
        max_severity_value = std::max(max_severity_value, static_cast<logging_severity_type>(logging_severity::info));
        max_severity_value = std::max(max_severity_value, static_cast<logging_severity_type>(logging_severity::warning));
        max_severity_value = std::max(max_severity_value, static_cast<logging_severity_type>(logging_severity::error));
        max_severity_value = std::max(max_severity_value, static_cast<logging_severity_type>(logging_severity::fatal));
    }

    return max_severity_value;
}

}
