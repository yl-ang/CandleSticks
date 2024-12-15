    cmake_minimum_required(VERSION 3.16)
    project(CandleSticks)

    set(CMAKE_CXX_STANDARD 20)

    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
    find_package(nlohmann_json 3.10.0 REQUIRED)
    add_executable(CandleSticks src/main.cpp
            src/Candlestick.cpp
            include/Candlestick.h
            include/CSVParser.h
            src/CSVParser.cpp
            src/ChartRenderer.cpp
            include/ChartRenderer.h
            include/AxisRenderer.h
            include/Tooltip.h
            include/ViewManager.h
            src/AxisRenderer.cpp
            src/Tooltip.cpp
            src/ViewManager.cpp)
    target_link_libraries(CandleSticks sfml-graphics sfml-window sfml-system)
    target_link_libraries(CandleSticks nlohmann_json::nlohmann_json)
    set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/nlohmann-json/share/cmake/nlohmann-json")