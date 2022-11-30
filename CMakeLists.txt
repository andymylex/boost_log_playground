cmake_minimum_required(VERSION 3.23)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake CACHE STRING "" FORCE)

project(BoostLogPlayground)

set(Boost_NO_WARN_NEW_VERSIONS 1)

find_package(Boost COMPONENTS log REQUIRED)

# ===== demo executables =====

add_executable(1TrivialLogging 1_trivial_logging.cpp)
target_link_libraries(1TrivialLogging Boost::log)

add_executable(2TrivialLoggingWithFilters 2_trivial_logging_with_filters.cpp)
target_link_libraries(2TrivialLoggingWithFilters Boost::log)

add_executable(3FileLogging 3_file_logging.cpp)
target_link_libraries(3FileLogging Boost::log)

add_executable(4CustomSink 4_custom_sink.cpp)
target_link_libraries(4CustomSink Boost::log)