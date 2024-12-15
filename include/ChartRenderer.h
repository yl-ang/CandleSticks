#ifndef CHART_RENDERER_H
#define CHART_RENDERER_H

#include <vector>
#include "Candlestick.h"
#include <SFML/Graphics.hpp>

class ChartRenderer {
public:
    ChartRenderer(const std::vector<Candlestick>& candlesticks, double minPrice, double maxPrice, const sf::Font& font);

    void render(sf::RenderWindow& window) const;
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);

    const Candlestick* getHoveredCandlestick(const sf::RenderWindow& window) const;

private:
    const std::vector<Candlestick>& candlesticks;
    double minPrice, maxPrice;
    float scale, width, spacing;
    sf::View graphView;

    void calculateScale();
};

#endif // CHART_RENDERER_H