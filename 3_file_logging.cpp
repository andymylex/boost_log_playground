#include <iostream>
#include <future>

#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;

void main()
{
    logging::add_common_attributes(); // to get %TimeStamp% working

    // 1. basic file logging
    // logging::add_file_log("sample.log");

    // 2. advanced file logging
    logging::add_file_log(
        logging::keywords::file_name = "sample_%N.log",
        logging::keywords::format = "[%TimeStamp%]: %Message%");

    logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);

    BOOST_LOG_TRIVIAL(trace) << "example trace message";
    BOOST_LOG_TRIVIAL(debug) << "example debug message";
    BOOST_LOG_TRIVIAL(info) << "example info message";
    BOOST_LOG_TRIVIAL(warning) << "example warning message";
    BOOST_LOG_TRIVIAL(error) << "example error message";
    BOOST_LOG_TRIVIAL(fatal) << "example fatal message";
}