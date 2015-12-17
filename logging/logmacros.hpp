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

#include <boost/current_function.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/log/utility/manipulators/to_log.hpp>

#define LOG(logger) BOOST_LOG(logger)
#define LOG_SEV(logger, severity) BOOST_LOG_SEV(logger, ebooks::logging::translate(severity))

#define LOG_ADDED_LOCATION(logger, severity, func, file, line)\
    LOG_SEV(logger, severity) << ::boost::log::add_value("Function", (std::string)func)\
                              << ::boost::log::add_value("SourceFile", (std::string)file)\
                              << ::boost::log::add_value("SourceLine", (unsigned int)line)

#define LOG_WITH_LOCATION(logger, severity) LOG_ADDED_LOCATION(logger, severity, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__)

#define LOG_FATAL(logger) LOG_WITH_LOCATION(logger, ebooks::logging::severity::fatal)
#define LOG_ERROR(logger) LOG_WITH_LOCATION(logger, ebooks::logging::severity::error)
#define LOG_WARNING(logger) LOG_WITH_LOCATION(logger, ebooks::logging::severity::warning)
#define LOG_INFO(logger) LOG_SEV(logger, ebooks::logging::severity::info)
#define LOG_DEBUG(logger) LOG_SEV(logger, ebooks::logging::severity::debug)
#define LOG_TRACE(logger) LOG_SEV(logger, ebooks::logging::severity::trace)
