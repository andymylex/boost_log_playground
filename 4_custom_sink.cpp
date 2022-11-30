#include <iostream>
#include <future>

#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <Windows.h>

namespace logging = boost::log;

class message_box_sink_backend : public logging::sinks::basic_formatted_sink_backend<
                                     char,
                                     logging::sinks::synchronized_feeding>
{
public:
    void consume(logging::record_view const &rec, std::string const &str)
    {
        const auto severity_level_ref = rec["Severity"].extract<logging::trivial::severity_level>();

        // prepare icon
        uint16_t icon;
        switch (severity_level_ref.get())
        {
            using logging::trivial::severity_level;

        case severity_level::info:
            icon = MB_ICONINFORMATION;
            break;
        case severity_level::warning:
            icon = MB_ICONWARNING;
            break;
        case severity_level::error:
        case severity_level::fatal:
            icon = MB_ICONERROR;
            break;
        default:
            icon = 0;
        }

        // prepare title
        std::stringstream ss;
        ss << severity_level_ref;
        auto severity_level_string = ss.str();
        severity_level_string[0] -= 32; // capitalize first letter

        MessageBoxA(nullptr, str.c_str(), severity_level_string.c_str(), MB_OK | icon);
    }
};

using message_box_sink = logging::sinks::synchronous_sink<message_box_sink_backend>;

void main()
{
    logging::add_common_attributes();

    auto sink = boost::make_shared<message_box_sink>();
    sink->set_formatter(logging::parse_formatter("[%TimeStamp%]: %Message%"));
    logging::core::get()->add_sink(sink);

    logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);

    BOOST_LOG_TRIVIAL(trace) << "example trace message";
    BOOST_LOG_TRIVIAL(debug) << "example debug message";
    BOOST_LOG_TRIVIAL(info) << "example info message";
    BOOST_LOG_TRIVIAL(warning) << "example warning message";
    BOOST_LOG_TRIVIAL(error) << "example error message";
    BOOST_LOG_TRIVIAL(fatal) << "example fatal message";
}