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

#include <algorithm>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/from_stream.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/utility/setup/filter_parser.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/expressions/predicates/channel_severity_filter.hpp>
#include <boost/log/core/core.hpp>

#include "util/enumclass.hpp"
#include "coreutil.hpp"
#include "logsource.hpp"

namespace ebooks
{
namespace logging
{

const std::string empty_path;
const std::string default_config_name("logging.config");

static void internal_logging_init()
{
    // enable logging
    if (!boost::log::core::get()->get_logging_enabled())
        boost::log::core::get()->set_logging_enabled();

    // init common core
    bool common_attributes_added = false;
    boost::log::attribute_value_set attributes;
    boost::log::record record = boost::log::core::get()->open_record(attributes);

    // check for attribute ThreadID
    if (record)
    {
        common_attributes_added = (record.attribute_values().find("ThreadID") != record.attribute_values().end());
    }

    // add common attributes they are still not added
    if (!common_attributes_added)
    {
        boost::log::add_common_attributes();
    }
}

BOOST_LOG_ATTRIBUTE_KEYWORD(severity_keyword, "Severity", boost::log::trivial::severity_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(channel_keyword, "Channel", std::string)

void initialize(const std::string& config_path_)
{
    internal_logging_init();

    // init from config file
    boost::filesystem::path config_file_path;

    if (!config_path_.empty())
    {
        if (boost::filesystem::exists(config_path_))
        {
            if (boost::filesystem::is_regular_file(config_path_))
                config_file_path = boost::filesystem::path(config_path_);
            else if (boost::filesystem::is_directory(config_path_) &&
                     boost::filesystem::exists(boost::filesystem::path(config_path_) / default_config_name))
                config_file_path = boost::filesystem::path(config_path_) / default_config_name;
        }
    }
    else
    {
        config_file_path = boost::filesystem::path(".") / default_config_name;
    }

    if (boost::filesystem::exists(config_file_path))
    {
        // init all from settings file
        boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");
        boost::log::register_simple_filter_factory<boost::log::trivial::severity_level, char>("Severity");
        boost::log::register_simple_formatter_factory<std::string, char>("Channel");
        boost::log::register_simple_filter_factory<std::string, char>("Channel");

        std::ifstream logging_config_file(boost::filesystem::system_complete(config_file_path).string().c_str());
        if (logging_config_file.is_open())
            boost::log::init_from_stream(logging_config_file);

        // init console sink
//        typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend> console_backend_type;
//        typedef boost::shared_ptr<console_backend_type> console_backend_ptr;
//        console_backend_ptr sink = boost::log::add_console_log(std::clog,
//                                                               boost::log::keywords::format = "%Message%",
//                                                               boost::log::keywords::auto_flush = true);
//        if (sink)
//        {
//            typedef boost::log::expressions::channel_severity_filter_actor<std::string, boost::log::trivial::severity_level> channel_severity_filter_type;
//            channel_severity_filter_type channel_severity_filter = boost::log::expressions::channel_severity_filter(channel_keyword, severity_keyword);
//            channel_severity_filter["APP"] = boost::log::trivial::info;
//            channel_severity_filter["COM"] = boost::log::trivial::warning;
//            channel_severity_filter["SYS"] = boost::log::trivial::warning;

//            sink->set_filter(channel_severity_filter);
//        }
    }
    else
    {
        // use default sink to console
    }
}

void reset()
{

}

log_source_ptr create_log_source(severity severity_, const std::string& channel_)
{
    return log_source_ptr(new log_source(severity_, channel_));
}

void log_message(const std::string& message_, severity severity_, const std::string& channel_)
{
    log_source logger(severity_, channel_);
    logger.log(message_);
}

boost::log::trivial::severity_level translate(severity severity_)
{
    return util::arrange<boost::log::trivial::severity_level>(util::integral(severity_));
}

severity translate(boost::log::trivial::severity_level severity_)
{
    return util::arrange<severity>(severity_);
}

boost::log::trivial::severity_level get_max_severity_value()
{
    static boost::log::trivial::severity_level max_severity_value = util::arrange<boost::log::trivial::severity_level>(0);

    if (max_severity_value == 0)
    {
        max_severity_value = std::max(max_severity_value, boost::log::trivial::trace);
        max_severity_value = std::max(max_severity_value, boost::log::trivial::debug);
        max_severity_value = std::max(max_severity_value, boost::log::trivial::info);
        max_severity_value = std::max(max_severity_value, boost::log::trivial::warning);
        max_severity_value = std::max(max_severity_value, boost::log::trivial::error);
        max_severity_value = std::max(max_severity_value, boost::log::trivial::fatal);
    }

    return max_severity_value;
}

boost::log::trivial::severity_level get_max_global_severity()
{
    boost::log::core_ptr core = boost::log::core::get();

    boost::log::attribute_value_set attr_severity;
    attr_severity.insert("Severity", boost::log::attributes::make_attribute_value(boost::log::trivial::warning));
    if (!core->open_record(attr_severity))
        return boost::log::trivial::error;

    attr_severity = boost::log::attribute_value_set();
    attr_severity.insert("Severity", boost::log::attributes::make_attribute_value(boost::log::trivial::info));
    if (!core->open_record(attr_severity))
        return boost::log::trivial::warning;

    attr_severity = boost::log::attribute_value_set();
    attr_severity.insert("Severity", boost::log::attributes::make_attribute_value(boost::log::trivial::debug));
    if (!core->open_record(attr_severity))
        return boost::log::trivial::info;

    attr_severity = boost::log::attribute_value_set();
    attr_severity.insert("Severity", boost::log::attributes::make_attribute_value(boost::log::trivial::trace));
    if (!core->open_record(attr_severity))
        return boost::log::trivial::debug;

    return boost::log::trivial::trace;
}

/**
 * @brief Static class used to stop logging at global till it is not initialized
 */
class turn_off_logging_on_load final
{
public:
    turn_off_logging_on_load()
    {
        boost::log::core::get()->set_logging_enabled(false);
    }

private:
    turn_off_logging_on_load& operator=(const turn_off_logging_on_load&) = delete;
    turn_off_logging_on_load(const turn_off_logging_on_load&) = delete;
};

static const turn_off_logging_on_load turn_off_logging_on_load_instance;


}
}
