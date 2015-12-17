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

#include "logsource.hpp"

namespace ebooks
{
namespace logging
{

log_source::log_source(severity severity_, const std::string& channel_) :
    severity_channel_source_type(severity_, channel_),
    _severity(severity_),
    _channel(channel_)
{ }

void log_source::log(const std::string& message_)
{
    log(_severity, _channel, message_);
}

void log_source::log(severity severity_, const std::string& message_)
{
    log(severity_, _channel, message_);
}

void log_source::log(severity severity_, const std::string& channel_, const std::string& message_)
{
    BOOST_LOG_STREAM_WITH_PARAMS(*this, (boost::log::keywords::channel = channel_)(boost::log::keywords::severity = translate(severity_))) << message_;
}

severity log_source::get_severity() const
{
    return _severity;
}

const std::string& log_source::get_channel() const
{
    return _channel;
}

}
}
