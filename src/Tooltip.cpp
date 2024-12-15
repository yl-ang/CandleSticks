#include "../include/Tooltip.h"
#include <iomanip>
#include <sstream>

Tooltip::Tooltip(const sf::Font &font) {
    tooltipText.setFont(font);
    tooltipText.setCharacterSize(14);
    tooltipText.setFillColor(sf::Color::Black);
    tooltipText.setStyle(sf::Text::Bold);

    tooltipBackground.setFillColor(sf::Color::White);
    tooltipBackground.setOutlineColor(sf::Color::Black);
    tooltipBackground.setOutlineThickness(1.0f);
}

void Tooltip::update(const sf::Vector2f &mousePosition, const Candlestick &candlestick) {
    std::ostringstream details;
    details << "Date: " << std::put_time(&candlestick.getTimestamp(), "%Y-%m-%d %H:%M:%S") << "\n"
            << "Open: " << candlestick.getOpen() << "\n"
            << "Close: " << candlestick.getClose() << "\n"
            << "High: " << candlestick.getHigh() << "\n"
            << "Low: " << candlestick.getLow();

    tooltipText.setString(details.str());

    tooltipBackground.setSize(sf::Vector2f(tooltipText.getGlobalBounds().width + 10.0f, tooltipText.getGlobalBounds().height + 10.0f));
    tooltipBackground.setPosition(mousePosition.x + 10.0f, mousePosition.y + 10.0f);
    tooltipText.setPosition(mousePosition.x + 15.0f, mousePosition.y + 15.0f);
}

void Tooltip::draw(sf::RenderWindow &window) {
    window.draw(tooltipBackground);
    window.draw(tooltipText);
}