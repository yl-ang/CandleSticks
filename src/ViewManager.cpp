#include "../include/ViewManager.h"

ViewManager::ViewManager(sf::RenderWindow& window)
    : window(window), zoomFactor(1.0f) {

    chartView.reset(sf::FloatRect(0, 0, 800, 650));
    axisView.reset(sf::FloatRect(0, 0, 800, 650));
}

void ViewManager::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Equal) {
            zoomFactor *= 0.9f;
            chartView.zoom(0.9f);
        } else if (event.key.code == sf::Keyboard::Dash) {
            zoomFactor *= 1.1f;
            chartView.zoom(1.1f);
        }
        window.setView(chartView);
    }
}

void ViewManager::setChartView() const {
    window.setView(chartView);
}

void ViewManager::setAxisView() const {
    window.setView(axisView);
}
