#include "../include/CSVParser.h"
#include "../include/Candlestick.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "../include/ChartRenderer.h"
#include "../include/Tooltip.h"
#include "../include/AxisRenderer.h"

int main() {
    // --- Load Data ---
    std::vector<Candlestick> candlesticks;
    if (!CSVParser::parseCSV("../data/data.csv", candlesticks)) {
        std::cerr << "Failed to parse CSV file!" << std::endl;
        return 1;
    }

    std::sort(candlesticks.begin(), candlesticks.end());

    // --- Initialize Components ---
    sf::RenderWindow window(sf::VideoMode(800, 650), "Candlestick Chart");
    window.setFramerateLimit(60);

    double minPrice = std::numeric_limits<double>::max();
    double maxPrice = std::numeric_limits<double>::min();

    for (const auto& candlestick : candlesticks) {
        minPrice = std::min(minPrice, std::min({candlestick.getOpen(), candlestick.getHigh(), candlestick.getLow(), candlestick.getClose()}));
        maxPrice = std::max(maxPrice, std::max({candlestick.getOpen(), candlestick.getHigh(), candlestick.getLow(), candlestick.getClose()}));
    }

    sf::Font font;
    if (!font.loadFromFile("../fonts/Arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    ChartRenderer chartRenderer(candlesticks, minPrice, maxPrice, font);

    Tooltip tooltip(font);

    AxisRenderer axisRenderer(font, 800.0f, 650.0f);

    sf::View graphView(sf::FloatRect(0, 0, 800, 650));
    window.setView(graphView);

    // --- Main Loop ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            chartRenderer.handleEvent(event, window);
        }

        window.clear(sf::Color::White);
        chartRenderer.render(window);

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition);

        const Candlestick *hoveredCandlestick = chartRenderer.getHoveredCandlestick(window);
        if (hoveredCandlestick) {
            tooltip.update(worldMousePosition, *hoveredCandlestick);
        }

        if (hoveredCandlestick) {
            window.setView(window.getDefaultView());
            tooltip.draw(window);
        }

        window.setView(window.getDefaultView());
        axisRenderer.drawXAxis(window, candlesticks);
        axisRenderer.drawYAxis(window, minPrice, maxPrice);

        window.display();
    }
    return 0;
}