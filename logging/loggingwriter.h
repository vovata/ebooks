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

#include "loggerdefine.h"
#include "ansicolors.h"

#include <string>

#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/log/sinks.hpp>

namespace common
{

class logging
{
public:
    typedef boost::unordered_map<logging_severity, const char*> severity_labels_map;
    typedef boost::unordered_map<logging_severity, ansi_color> severity_colors_map;

    static void create_console_writer(const std::string& name);
    static void create_file_writer(const std::string& name, const std::string& file_path);
    static void disable_writer(const std::string& name);
    static void enable_writer(const std::string& name);
    static bool writer_is_active(const std::string& name);

    static void set_default_severity_labels(const std::string& name);
    static void set_default_severity_colors(const std::string& name);

    logging& operator=(const logging&) = delete;
    logging(const logging&) = delete;

private:
    class writer
    {
    public:
        virtual ~writer() { }

        virtual void init() = 0;
        virtual void enable() = 0;
        virtual void disable() = 0;
        virtual void set_formatter() = 0;
        virtual bool is_active() const;

        void set_severity_labels(const severity_labels_map& severity_labels);
        void switch_severity_labels(switch_output switch_value);
        const std::string& get_severity_label(logging_severity severity) const;
        const std::string& get_severity_color(logging_severity severity) const;

        void set_severity_colors(const severity_colors_map& severity_colors);
        void switch_severity_colors(switch_output switch_value);

        void switch_channel_label(switch_output switch_value);
        void switch_tag_label(switch_output switch_value);

        virtual void function_formatter(boost::log::record_view const& rec, boost::log::formatting_ostream& strm);

    protected:
        writer(const std::string& name);

        bool _is_active;

    private:
        typedef std::vector<std::string> severity_labels_array;
        typedef std::vector<std::string> severity_colors_array;

        std::string _name;

        severity_labels_array _severity_labels;
        severity_colors_array _severity_colors;
        std::string _normal_color;

        switch_output _switch_severity_labels;
        switch_output _switch_severity_colors;
        switch_output _switch_channel_label;
        switch_output _switch_tag_label;
    };

    class empty_writer : public writer
    {
    public:
        empty_writer() : writer("") { }
        void init() override { }
        void enable() override { }
        void disable() override { }
        void set_formatter() override { }
        bool is_active() const override { return false; }
    };

    class console_writer : public writer
    {
    public:
        console_writer(const std::string& name) :
            writer(name)
        { }

        ~console_writer() override;

        void init() override;
        void enable() override;
        void disable() override;
        void set_formatter() override;

    private:
        boost::shared_ptr<boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend> > _sink;
    };

    class file_writer : public writer
    {
    public:
        file_writer(const std::string& name, const std::string& file_path) :
            writer(name),
            _file_path(file_path)
        { }

        ~file_writer() override;

        void init() override;
        void enable() override;
        void disable() override;
        void set_formatter() override;

    private:
        std::string _file_path;
        boost::shared_ptr<boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend> > _sink;
    };

    static logging& get_logging_core();

    logging();
    writer& get_writer(const std::string& name);

    typedef boost::unordered_map<std::string, boost::shared_ptr<writer> > writers_map_type;
    writers_map_type writers;
};

}
