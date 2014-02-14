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

#include <iomanip>

#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>

namespace common
{
void logging::create_console_writer(const std::string& name)
{
    boost::shared_ptr<console_writer> writer_ptr = boost::make_shared<console_writer>(name);
    writer_ptr->init();
    get_logging_core().writers.emplace(name, writer_ptr);
}

void logging::create_file_writer(const std::string& name, const std::string& file_path)
{
    boost::shared_ptr<file_writer> writer_ptr = boost::make_shared<file_writer>(name, file_path);
    writer_ptr->init();
    get_logging_core().writers.emplace(name, writer_ptr);
}

void logging::disable_writer(const std::string& name)
{
    get_logging_core().get_writer(name).disable();
}

void logging::enable_writer(const std::string& name)
{
    get_logging_core().get_writer(name).enable();
}

bool logging::writer_is_active(const std::string& name)
{
    return get_logging_core().get_writer(name).is_active();
}

void logging::set_default_severity_labels(const std::string& name)
{
    writer& the_writer = get_logging_core().get_writer(name);

    static severity_labels_map severity_labels;

    if (severity_labels.empty())
    {
        severity_labels[logging_severity::fatal]    = "(fatal) ";
        severity_labels[logging_severity::error]    = "(error) ";
        severity_labels[logging_severity::warning]  = "(warning) ";
        severity_labels[logging_severity::info]     = "(info) ";
        severity_labels[logging_severity::debug]    = "(debug) ";
        severity_labels[logging_severity::trace]    = "(trace) ";
    }

    the_writer.set_severity_labels(severity_labels);
}

void logging::set_default_severity_colors(const std::string& name)
{
    writer& the_writer = get_logging_core().get_writer(name);

    static severity_colors_map severity_colors;
    if (severity_colors.empty())
    {
        severity_colors[logging_severity::fatal]    = ansi_color(ansi_color_code::magenta, ansi_color_effect::bold);
        severity_colors[logging_severity::error]    = ansi_color(ansi_color_code::red, ansi_color_effect::bold);
        severity_colors[logging_severity::warning]  = ansi_color(ansi_color_code::yellow, ansi_color_effect::bold);
        severity_colors[logging_severity::info]     = ansi_color(ansi_color_code::green, ansi_color_effect::normal);
        severity_colors[logging_severity::debug]    = ansi_color(ansi_color_code::cyan, ansi_color_effect::normal);
        severity_colors[logging_severity::trace]    = ansi_color(ansi_color_code::white, ansi_color_effect::normal);
    }

    the_writer.set_severity_colors(severity_colors);
}

logging& logging::get_logging_core()
{
    static logging log_object;
    return log_object;
}

logging::writer& logging::get_writer(const std::string& name)
{
    writers_map_type::iterator it_writer = get_logging_core().writers.find(name);
    if (it_writer == get_logging_core().writers.end())
    {
        static empty_writer empty_one;
        return empty_one;
    }

    writer& the_writer = *it_writer->second.get();
    return the_writer;
}

logging::logging()
{ }

logging::writer::writer(const std::string &name) :
    _is_active(false),
    _name(name),
    _switch_severity_labels(switch_output::off),
    _switch_severity_colors(switch_output::off),
    _switch_channel_label(switch_output::off),
    _switch_tag_label(switch_output::off)
{ }

bool logging::writer::is_active() const
{
    return _is_active;
}

void logging::writer::set_severity_labels(const severity_labels_map& severity_labels)
{
    logging_severity_type max_severity_value = get_max_logging_severity_value();

    _severity_labels.clear();
    _severity_labels.resize(max_severity_value + 1);
    for (const severity_labels_map::value_type& severity_label_value : severity_labels)
    {
        std::size_t array_index = static_cast<logging_severity_type>(severity_label_value.first);
        _severity_labels[array_index] = severity_label_value.second;
    }

    _switch_severity_labels = switch_output::on;
}

void logging::writer::switch_severity_labels(switch_output switch_value)
{
    _switch_severity_labels = switch_value;
}

const std::string& logging::writer::get_severity_label(logging_severity severity) const
{
    static std::string empty_label;

    logging_severity_type severity_level = static_cast<logging_severity_type>(severity);
    if (severity_level >= _severity_labels.size())
        return empty_label;

    return _severity_labels[severity_level];
}

const std::string& logging::writer::get_severity_color(logging_severity severity) const
{
    static std::string empty_color;

    logging_severity_type severity_level = static_cast<logging_severity_type>(severity);
    if (severity_level >= _severity_colors.size())
        return empty_color;

    return _severity_colors[severity_level];
}

void logging::writer::set_severity_colors(const severity_colors_map& severity_colors)
{
    std::stringstream normal_color_stream;
    normal_color_stream << static_cast<ansi_color_style_type>(ansi_color_style::normal) << "[";

    logging_severity_type max_severity_value = get_max_logging_severity_value();

    _severity_colors.clear();
    _severity_colors.resize(max_severity_value + 1);
    for (const severity_colors_map::value_type& severity_color_value : severity_colors)
    {
        std::size_t array_index = static_cast<logging_severity_type>(severity_color_value.first);
        const ansi_color& color = severity_color_value.second;

        std::stringstream color_stream;
        color_stream << normal_color_stream.str();
        color_stream << std::setw(1) << static_cast<ansi_color_effect_type>(color.effect) << ";"
                     << std::setw(2) << static_cast<ansi_color_code_type>(color.code) << ";40m";
        _severity_colors[array_index] = color_stream.str();
    }

    normal_color_stream << std::setw(1) << static_cast<ansi_color_effect_type>(ansi_color_effect::normal) << "m";
    _normal_color = normal_color_stream.str();

    _switch_severity_colors = switch_output::on;
}

void logging::writer::switch_severity_colors(switch_output switch_value)
{
     _switch_severity_colors = switch_value;
}

void logging::writer::switch_channel_label(switch_output switch_value)
{
     _switch_channel_label = switch_value;
}

void logging::writer::switch_tag_label(switch_output switch_value)
{
     _switch_tag_label = switch_value;
}

void logging::writer::function_formatter(boost::log::record_view const& rec, boost::log::formatting_ostream& strm)
{
    if (_switch_severity_labels == switch_output::on ||
        _switch_severity_colors == switch_output::on)
    {
        logging_severity severity = boost::log::extract<logging_severity>("Severity", rec).get();

        if (_switch_severity_colors == switch_output::on)
            strm << get_severity_color(severity);

        if (_switch_severity_labels == switch_output::on)
            strm << get_severity_label(severity);
    }

    strm << rec[boost::log::expressions::smessage];

    if (_switch_severity_colors == switch_output::on)
        strm << _normal_color;
}

logging::console_writer::~console_writer()
{
    disable();
}

void logging::console_writer::init()
{
    if (_is_active)
        return;

    _sink = boost::log::add_console_log();
    _sink->locked_backend()->auto_flush(true);

    set_formatter();

    _is_active = true;
}

void logging::console_writer::enable()
{
    if (_is_active)
        return;

    boost::log::core::get()->add_sink(_sink);
    _is_active = true;
}

void logging::console_writer::disable()
{
    if (!_is_active)
        return;

    boost::log::core::get()->remove_sink(_sink);
    _sink->flush();
    _is_active = false;
}

void logging::console_writer::set_formatter()
{
    _sink->set_formatter(boost::bind(&logging::writer::function_formatter, this, _1, _2));
}

logging::file_writer::~file_writer()
{
    disable();
}

void logging::file_writer::init()
{
    if (_is_active)
        return;

    _sink = boost::log::add_file_log(_file_path.c_str());
    _sink->locked_backend()->auto_flush(true);

    set_formatter();

    _is_active = true;
}

void logging::file_writer::enable()
{
    if (_is_active)
        return;

    boost::log::core::get()->add_sink(_sink);
    _is_active = true;
}

void logging::file_writer::disable()
{
    if (!_is_active)
        return;

    boost::log::core::get()->remove_sink(_sink);
    _sink->flush();
    _is_active = false;
}

void logging::file_writer::set_formatter()
{
    _sink->set_formatter(boost::bind(&logging::writer::function_formatter, this, _1, _2));
}

}
