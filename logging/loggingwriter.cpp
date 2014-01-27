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

#include "loggingwriter.h"

#include <boost/log/utility/setup/console.hpp>

namespace common
{

logging::writers_map_type logging::writers;

void logging::create_writer(const std::string& name)
{
    boost::shared_ptr<writer> writer_ptr = boost::make_shared<writer>(name);
    writer_ptr->init();
    get_logging_core().writers.emplace(name, writer_ptr);
}

logging& logging::get_logging_core()
{
    static logging log_object;
    return log_object;
}

logging::logging()
{ }

logging::writer::writer(const std::string &name) :
    _name(name)
{ }

void logging::writer::init()
{
    _sink = boost::log::add_console_log();
    _sink->locked_backend()->auto_flush(true);
}

void logging::writer::enable()
{
    boost::log::core::get()->add_sink(_sink);
}

void logging::writer::disable()
{
    boost::log::core::get()->remove_sink(_sink);
    _sink->flush();
}

}
