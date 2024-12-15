#include "../include/CSVParser.h"
#include "../include/Candlestick.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <ctime>

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

    float scale = 500.0f / (maxPrice - minPrice);

    float totalWidth = 800.0f;
    float width = totalWidth / candlesticks.size() * 0.7f;
    float spacing = totalWidth / candlesticks.size() * 0.3f;

    sf::Font font;
    if (!font.loadFromFile("../fonts/Arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    sf::Text xAxisLabel("Date", font, 18);
    xAxisLabel.setFillColor(sf::Color::Black);
    xAxisLabel.setPosition(370.0f, 610.0f);

    sf::Text yAxisLabel("Price", font, 18);
    yAxisLabel.setFillColor(sf::Color::Black);
    yAxisLabel.setRotation(-90.0f);
    yAxisLabel.setPosition(10.0f, 250.0f);

    sf::Text tooltipText("", font, 14);
    tooltipText.setFillColor(sf::Color::Black);
    tooltipText.setStyle(sf::Text::Bold);

    sf::RectangleShape tooltipBackground(sf::Vector2f(150.0f, 80.0f));
    tooltipBackground.setFillColor(sf::Color::White);
    tooltipBackground.setOutlineColor(sf::Color::Black);
    tooltipBackground.setOutlineThickness(1.0f);

    sf::View graphView(sf::FloatRect(0, 0, 800, 650));
    sf::View axisView(sf::FloatRect(0, 0, 800, 650));

    // Zoom factor
    float zoomFactor = 1.0f;

    // --- Main Loop ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Equal) {
                    zoomFactor *= 0.9f;
                    graphView.zoom(0.9f);
                } else if (event.key.code == sf::Keyboard::Dash) {
                    zoomFactor *= 1.1f;
                    graphView.zoom(1.1f);
                }
                window.setView(graphView);
            }
        }

        window.clear(sf::Color::White);

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition, graphView);

        float xPosition = 0.0f;
        bool hoverDetected = false;

        window.setView(graphView);
        for (size_t i = 0; i < candlesticks.size(); ++i) {
            const auto& candlestick = candlesticks[i];
            float openPos = 600.0f - (candlestick.getOpen() - minPrice) * scale;
            float closePos = 600.0f - (candlestick.getClose() - minPrice) * scale;
            float highPos = 600.0f - (candlestick.getHigh() - minPrice) * scale;
            float lowPos = 600.0f - (candlestick.getLow() - minPrice) * scale;

            sf::RectangleShape candleBody(sf::Vector2f(width, std::abs(openPos - closePos)));
            candleBody.setPosition(xPosition, openPos < closePos ? closePos : openPos);
            candleBody.setFillColor(candlestick.getOpen() > candlestick.getClose() ? sf::Color::Red : sf::Color::Green);

            sf::RectangleShape candleWick(sf::Vector2f(1.5f, std::abs(highPos - lowPos)));
            candleWick.setPosition(xPosition + width / 2.0f - 1.0f, lowPos);
            candleWick.setFillColor(sf::Color::Black);

            window.draw(candleBody);
            window.draw(candleWick);

            if (!hoverDetected &&
                worldMousePosition.x >= xPosition &&
                worldMousePosition.x <= xPosition + width &&
                worldMousePosition.y >= std::min(openPos, closePos) &&
                worldMousePosition.y <= std::max(openPos, closePos)) {

                hoverDetected = true;

                std::ostringstream details;
                details << "Date: " << std::put_time(&candlestick.getTimestamp(), "%Y-%m-%d %H:%M:%S") << "\n"
                        << "Open: " << candlestick.getOpen() << "\n"
                        << "Close: " << candlestick.getClose() << "\n"
                        << "High: " << candlestick.getHigh() << "\n"
                        << "Low: " << candlestick.getLow();

                tooltipText.setString(details.str());
                tooltipBackground.setSize(sf::Vector2f(tooltipText.getGlobalBounds().width + 10.0f,
                                                       tooltipText.getGlobalBounds().height + 10.0f));
                tooltipBackground.setPosition(worldMousePosition.x + 10.0f, worldMousePosition.y + 10.0f);
                tooltipText.setPosition(worldMousePosition.x + 15.0f, worldMousePosition.y + 15.0f);
            }


            std::tm timestamp = candlestick.getTimestamp();
            int currentMonth = timestamp.tm_mon;


            if (i == 0 || currentMonth != candlesticks[i-1].getTimestamp().tm_mon) {
                std::ostringstream monthLabel;
                monthLabel << std::put_time(&timestamp, "%b");

                sf::Text monthText(monthLabel.str(), font, 12);
                monthText.setFillColor(sf::Color::Black);
                monthText.setPosition(xPosition + width / 2 - monthText.getGlobalBounds().width / 2, 620.0f);
                window.draw(monthText);
            }

            xPosition += width + spacing;
        }

        if (hoverDetected) {
            window.setView(window.getDefaultView());
            window.draw(tooltipBackground);
            window.draw(tooltipText);
        }

        window.setView(axisView);
        window.draw(xAxisLabel);
        window.draw(yAxisLabel);

        window.display();
    }

    return 0;
}