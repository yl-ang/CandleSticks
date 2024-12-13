#include "../include/CSVParser.h"
#include "../include/Candlestick.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>

int main() {
    std::vector<Candlestick> candlesticks;

    if (!CSVParser::parseCSV("../data/data.csv", candlesticks)) {
        std::cerr << "Failed to parse CSV file!" << std::endl;
        return 1;
    }

    std::sort(candlesticks.begin(), candlesticks.end(), [](const Candlestick& a, const Candlestick& b) {
        return a.getTimestamp() < b.getTimestamp();
    });

    // SFML window setup
    sf::RenderWindow window(sf::VideoMode(800, 600), "Candlestick Chart");
    window.setFramerateLimit(60);

    double minPrice = std::numeric_limits<double>::max();
    double maxPrice = std::numeric_limits<double>::min();

    for (const auto& candlestick : candlesticks) {
        minPrice = std::min(minPrice, std::min({candlestick.getOpen(), candlestick.getHigh(), candlestick.getLow(), candlestick.getClose()}));
        maxPrice = std::max(maxPrice, std::max({candlestick.getOpen(), candlestick.getHigh(), candlestick.getLow(), candlestick.getClose()}));
    }

    float scale = 600.0f / (maxPrice - minPrice);

    float width = 2.0f;
    float spacing = 1.0f;

    sf::Font font;
    if (!font.loadFromFile("../fonts/Arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    sf::Text xAxisLabel("Date", font, 18);
    xAxisLabel.setPosition(370.0f, 580.0f);

    sf::Text yAxisLabel("Price", font, 18);
    yAxisLabel.setPosition(10.0f, 250.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        float xPosition = 50.0f;

        for (const auto& candlestick : candlesticks) {
            float openPos = 600.0f - (candlestick.getOpen() - minPrice) * scale;
            float closePos = 600.0f - (candlestick.getClose() - minPrice) * scale;
            float highPos = 600.0f - (candlestick.getHigh() - minPrice) * scale;
            float lowPos = 600.0f - (candlestick.getLow() - minPrice) * scale;

            sf::RectangleShape candleBody(sf::Vector2f(width, std::abs(openPos - closePos)));
            candleBody.setPosition(xPosition, openPos < closePos ? closePos : openPos);
            candleBody.setFillColor(candlestick.getOpen() > candlestick.getClose() ? sf::Color::Red : sf::Color::Green);

            sf::RectangleShape candleWick(sf::Vector2f(2.0f, std::abs(highPos - lowPos)));
            candleWick.setPosition(xPosition + width / 2.0f - 1.0f, lowPos);
            candleWick.setFillColor(sf::Color::Black);

            window.draw(candleBody);
            window.draw(candleWick);

            sf::Text dateLabel(candlestick.getTimestamp(), font, 10);
            dateLabel.setPosition(xPosition, 590.0f);  // Place the date below the candlestick
            window.draw(dateLabel);

            xPosition += width + spacing;
        }

        window.draw(xAxisLabel);
        window.draw(yAxisLabel);

        window.display();
    }

    return 0;
}