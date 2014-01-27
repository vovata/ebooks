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

#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/log/sinks.hpp>

namespace common
{

class logging
{
public:
    static void create_writer(const std::string& name);

    logging& operator=(const logging&) = delete;
    logging(const logging&) = delete;

private:
    static logging& get_logging_core();
    logging();

    class writer
    {
    public:
        writer(const std::string& name);
        void init();
        void enable();
        void disable();

    private:
        std::string _name;

        boost::shared_ptr<boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend> > _sink;
    };

    typedef boost::unordered_map<std::string, boost::shared_ptr<writer> > writers_map_type;
    static writers_map_type writers;
};

}
