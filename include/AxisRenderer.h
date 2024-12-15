#ifndef AXIS_RENDERER_H
#define AXIS_RENDERER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Candlestick.h"

class AxisRenderer {
public:
    AxisRenderer(const sf::Font& font, float chartWidth, float chartHeight);
    void drawXAxis(sf::RenderWindow &window, const std::vector<Candlestick> &candlesticks) const;
    void drawYAxis(sf::RenderWindow &window, double minPrice, double maxPrice) const;

private:
    const sf::Font& font;
    float chartWidth;
    float chartHeight;
};

#endif // AXIS_RENDERER_H