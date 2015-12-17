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

#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/channel_feature.hpp>
#include <boost/log/attributes/mutable_constant.hpp>

#include "loggerdefine.hpp"
#include "coreutil.hpp"

namespace ebooks
{
namespace logging
{

/**
 * @brief Base class for logging source.
 */
template<typename LevelT = int, typename ChannelT = std::string>
class severity_channel_source : public boost::log::sources::basic_composite_logger<
        char,
        severity_channel_source<LevelT, ChannelT>,
        boost::log::sources::single_thread_model,
        boost::log::sources::features<
            boost::log::sources::severity<LevelT>,
            boost::log::sources::channel<ChannelT>
        >
    >
{
    typedef typename severity_channel_source::logger_base base_type;

public:
    explicit severity_channel_source(severity severity_);
    explicit severity_channel_source(severity severity_, ChannelT channel_name_);

    boost::log::record open_record();

    template<typename ArgsT>
    boost::log::record open_record(ArgsT const& args)
    {
        // Perform a quick check first
        boost::log::trivial::severity_level severity_value = args[boost::log::keywords::severity | boost::log::trivial::trace];
        if (severity_value >= _severity_max_level)
        {
            return base_type::open_record(args);
        }

        return boost::log::record();
    }

private:
    boost::log::trivial::severity_level _severity_level;
    boost::log::trivial::severity_level _severity_max_level;
};

}
}
