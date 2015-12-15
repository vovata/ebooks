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

#include <iostream>

#include "logging/loggingwriter.hpp"
#include "logging/loggerdefine.hpp"

#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

int main()
{
    ebooks::logging::facility::create_console_writer("console");
    ebooks::logging::facility::set_default_severity_colors("console");
    ebooks::logging::facility::create_file_writer("file_log", "file.log");
    ebooks::logging::facility::set_default_severity_labels("file_log");

    boost::log::sources::severity_logger<ebooks::logging::severity> logger(boost::log::keywords::severity = ebooks::logging::severity::info);

    BOOST_LOG(logger) << "Hello World!";

    BOOST_LOG_SEV(logger, ebooks::logging::severity::trace) << "trace messgae";
    BOOST_LOG_SEV(logger, ebooks::logging::severity::debug) << "debug text";
    BOOST_LOG_SEV(logger, ebooks::logging::severity::info) << "just info";
    BOOST_LOG_SEV(logger, ebooks::logging::severity::warning) << "attention";
    BOOST_LOG_SEV(logger, ebooks::logging::severity::error) << "ERROR";
    BOOST_LOG_SEV(logger, ebooks::logging::severity::fatal) << "FATAL";

    return 0;
}

