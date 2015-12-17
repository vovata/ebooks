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

#include "severitychannel.hpp"

namespace ebooks
{
namespace logging
{

template<typename LevelT, typename ChannelT>
severity_channel_source<LevelT, ChannelT>::severity_channel_source(severity severity_) :
    base_type(boost::log::keywords::severity = translate(severity_)),
    _severity_level(translate(severity_)),
    _severity_max_level(get_max_global_severity())
{ }

template<typename LevelT, typename ChannelT>
severity_channel_source<LevelT, ChannelT>::severity_channel_source(severity severity_, ChannelT channel_name_) :
    base_type((boost::log::keywords::severity = translate(severity_), boost::log::keywords::channel = channel_name_)),
    _severity_level(translate(severity_)),
    _severity_max_level(get_max_global_severity())
{ }

template<typename LevelT, typename ChannelT>
boost::log::record severity_channel_source<LevelT, ChannelT>::open_record()
{
    if (_severity_level >= _severity_max_level)
    {
        return base_type::open_record();
    }

    return boost::log::record();
}

template class severity_channel_source<boost::log::trivial::severity_level, std::string>;

}
}
