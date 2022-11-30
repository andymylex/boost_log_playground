#include <iostream>
#include <future>

#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

namespace logging = boost::log;

void main()
{
    logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);

    BOOST_LOG_TRIVIAL(trace) << "example trace message";
    BOOST_LOG_TRIVIAL(debug) << "example debug message";
    BOOST_LOG_TRIVIAL(info) << "example info message";
    BOOST_LOG_TRIVIAL(warning) << "example warning message";
    BOOST_LOG_TRIVIAL(error) << "example error message";
    BOOST_LOG_TRIVIAL(fatal) << "example fatal message";
}