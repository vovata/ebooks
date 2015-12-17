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

#pragma once

#include <string>

#include <boost/log/trivial.hpp>

#include "loggerdefine.hpp"
#include "logsourcefwd.hpp"

namespace ebooks
{
namespace logging
{

extern const std::string empty_path;
extern const std::string default_config_name;

/**
 * @brief Helper for global initialization of the logging environment
 */
void initialize(const std::string& config_path_ = empty_path);

/**
 * @brief Helper for global reset of the logging environment
 */
void reset();

/**
 * @brief Get an accessor to the logging functionality
 */
log_source_ptr create_log_source(severity severity_ = severity::trace, const std::string& channel_ = "");
/**
 * @brief Short way to put a message in the logging system (without additional attributes)
 */
void log_message(const std::string& message, severity severity_ = severity::trace, const std::string& channel_ = "");

/**
 * @brief Internal translate from 'severity' to trivial boost log enum
 */
boost::log::trivial::severity_level translate(severity severity_);
/**
 * @brief Internal translate from trivial boost log enum to 'severity'
 */
severity translate(boost::log::trivial::severity_level severity_);

/**
 * @brief Returns the maximum global severity level at all
 */
boost::log::trivial::severity_level get_max_severity_value();
/**
 * @brief Returns the maximum global severity level currently used
 */
boost::log::trivial::severity_level get_max_global_severity();


}
}
