#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

#include <SFML/Graphics.hpp>

class ViewManager {
public:
    explicit ViewManager(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event);
    void setChartView() const;
    void setAxisView() const;
    sf::View& getChartView() { return chartView; }

private:
    sf::RenderWindow& window;
    sf::View chartView;
    sf::View axisView;

    float zoomFactor;
};

#endif // VIEW_MANAGER_H