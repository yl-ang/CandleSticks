#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <SFML/Graphics.hpp>
#include "Candlestick.h"

class Tooltip {
public:
    Tooltip(const sf::Font &font);
    void update(const sf::Vector2f &mousePosition, const Candlestick &candlestick);
    void draw(sf::RenderWindow &window);

private:
    sf::Text tooltipText;
    sf::RectangleShape tooltipBackground;
};

#endif // TOOLTIP_H