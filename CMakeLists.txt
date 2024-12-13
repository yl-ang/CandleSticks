cmake_minimum_required(VERSION 3.16)
project(CandleSticks)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(nlohmann_json 3.10.0 REQUIRED)
add_executable(CandleSticks main.cpp)
target_link_libraries(CandleSticks sfml-graphics sfml-window sfml-system)
target_link_libraries(CandleSticks nlohmann_json::nlohmann_json)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/nlohmann-json/share/cmake/nlohmann-json")