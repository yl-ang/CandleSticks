#include "../include/ChartRenderer.h"
#include <sstream>

ChartRenderer::ChartRenderer(const std::vector<Candlestick> &candlesticks, double minPrice, double maxPrice, const sf::Font &font)
    : candlesticks(candlesticks), minPrice(minPrice), maxPrice(maxPrice) {
    graphView.reset(sf::FloatRect(0, 0, 800, 650));
    calculateScale();

    float totalWidth = 800.0f;
    width = totalWidth / candlesticks.size() * 0.7f;
    spacing = totalWidth / candlesticks.size() * 0.3f;
}

void ChartRenderer::calculateScale() {
    scale = 500.0f / (maxPrice - minPrice);
}

void ChartRenderer::render(sf::RenderWindow &window) const {
    window.setView(graphView);

    float xPosition = 50.0f;  // Start after the Y-axis

    for (const auto& candlestick : candlesticks) {
        float openPos = 600.0f - (candlestick.getOpen() - minPrice) * scale;
        float closePos = 600.0f - (candlestick.getClose() - minPrice) * scale;
        float highPos = 600.0f - (candlestick.getHigh() - minPrice) * scale;
        float lowPos = 600.0f - (candlestick.getLow() - minPrice) * scale;

        sf::RectangleShape candleBody(sf::Vector2f{width, std::abs(openPos - closePos)});
        candleBody.setPosition(xPosition, openPos < closePos ? closePos : openPos);
        candleBody.setFillColor(candlestick.getOpen() > candlestick.getClose() ? sf::Color::Red : sf::Color::Green);

        sf::RectangleShape candleWick(sf::Vector2f{2.0f, std::abs(highPos - lowPos)});
        candleWick.setPosition(xPosition + width / 2.0f - 1.0f, lowPos);
        candleWick.setFillColor(sf::Color::Black);

        window.draw(candleBody);
        window.draw(candleWick);

        xPosition += width + spacing;
    }
}

void ChartRenderer::handleEvent(const sf::Event &event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Equal) {
            graphView.zoom(0.9f);
        } else if (event.key.code == sf::Keyboard::Dash) {
            graphView.zoom(1.1f);
        }
        window.setView(graphView);
    }
}

const Candlestick *ChartRenderer::getHoveredCandlestick(const sf::RenderWindow &window) const {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition, graphView);

    float xPosition = 0.0f;

    for (const auto& candlestick : candlesticks) {
        const float candlestickLeft = xPosition;
        const float candlestickRight = xPosition + width;

        float openPos = 600.0f - (candlestick.getOpen() - minPrice) * scale;
        float closePos = 600.0f - (candlestick.getClose() - maxPrice) * scale;

        if (worldMousePosition.x >= candlestickLeft &&
            worldMousePosition.x <= candlestickRight &&
            worldMousePosition.y >= std::min(openPos, closePos) &&
            worldMousePosition.y <= std::max(openPos, closePos)) {
            return &candlestick;
        }
        xPosition += width + spacing;
    }
    return nullptr;
}

float ChartRenderer::getZoomFactor() const {
    return scale;
}