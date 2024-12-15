#include "../include/AxisRenderer.h"
#include <sstream>
#include <iomanip>

AxisRenderer::AxisRenderer(const sf::Font &font, float chartWidth, float chartHeight)
    : font(font), chartWidth(chartWidth), chartHeight(chartHeight) {}

void AxisRenderer::drawXAxis(sf::RenderWindow &window, const std::vector<Candlestick> &candlesticks) const {
    sf::RectangleShape xAxisLine(sf::Vector2f(chartWidth, 2.0f));
    xAxisLine.setFillColor(sf::Color::Black);
    xAxisLine.setPosition(0.0f, chartHeight - 50.0f);
    window.draw(xAxisLine);

    float spacing = chartWidth / candlesticks.size();
    for (size_t i = 0; i < candlesticks.size(); ++i) {
        const auto& candlestick = candlesticks[i];

        std::tm timestamp = candlestick.getTimestamp();
        if (i == 0 || timestamp.tm_mon != candlesticks[i - 1].getTimestamp().tm_mon) {
            std::ostringstream label;
            label << std::put_time(&timestamp, "%b");

            sf::Text text(label.str(), font, 12);
            text.setFillColor(sf::Color::Black);
            text.setPosition(i * spacing, chartHeight - 30.0f);
            window.draw(text);
        }
    }
}

void AxisRenderer::drawYAxis(sf::RenderWindow &window, double minPrice, double maxPrice) const {
    sf::RectangleShape yAxisLine(sf::Vector2f(2.0f, chartHeight - 50.0f));
    yAxisLine.setFillColor(sf::Color::Black);
    yAxisLine.setPosition(50.0f, 0.0f);
    window.draw(yAxisLine);

    int numTicks = 10;
    float tickSpacing = (chartHeight - 50.0f) / numTicks;
    double priceIncrement = (maxPrice - minPrice) / numTicks;

    for (int i = 0; i <= numTicks; ++i) {
        float yPos = chartHeight - 50.0f - (i * tickSpacing);
        double price = minPrice + (i * priceIncrement);

        sf::Text text(std::to_string(static_cast<int>(price)), font, 12);
        text.setFillColor(sf::Color::Black);
        text.setPosition(10.0f, yPos - text.getGlobalBounds().height / 2.0f);
        window.draw(text);

        sf::RectangleShape tickMark(sf::Vector2f(5.0f, 2.0f));
        tickMark.setFillColor(sf::Color::Black);
        tickMark.setPosition(45.0f, yPos);
        window.draw(tickMark);
    }
}