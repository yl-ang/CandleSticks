#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <limits>

int main() {
    std::ifstream input("../data/test.json");
    if (!input.is_open()) {
        std::cerr << "Failed to open test.json!" << std::endl;
        return 1;
    }

    nlohmann::json j;
    try {
        input >> j;
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        return 1;
    }

    if (!j.contains("candlesticks")) {
        std::cerr << "No candlestick data found in the JSON file!" << std::endl;
        return 1;
    }

    // SFML window setup (larger window size)
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Candlestick Chart");

    // Define properties for rendering candlesticks
    float width = 20.0f;  // Increase width of each candlestick
    float maxHeight = 800.0f;  // Window height
    float scale = 2.0f;  // Scaling factor for the chart

    // Find max and min prices to adjust scaling dynamically
    float maxPrice = 0.0f;
    float minPrice = std::numeric_limits<float>::max();

    for (const auto& candlestick : j["candlesticks"]) {
        float high = candlestick["high"];
        float low = candlestick["low"];
        maxPrice = std::max(maxPrice, high);
        minPrice = std::min(minPrice, low);
    }

    // Dynamically scale based on the range of prices
    float priceRange = maxPrice - minPrice;
    scale = window.getSize().y / priceRange;  // Scale the chart to fit the window height

    // Create a vector to hold candlestick shapes
    std::vector<sf::RectangleShape> candlesticks;

    // Loop through each candlestick in the JSON and create SFML rectangles
    for (const auto& candlestick : j["candlesticks"]) {
        float open = candlestick["open"];
        float close = candlestick["close"];
        float high = candlestick["high"];
        float low = candlestick["low"];

        // Scale the values to fit within the window
        float openPos = maxHeight - ((open - minPrice) * scale);
        float closePos = maxHeight - ((close - minPrice) * scale);
        float highPos = maxHeight - ((high - minPrice) * scale);
        float lowPos = maxHeight - ((low - minPrice) * scale);

        // Create candlestick shapes (body and wick)
        sf::RectangleShape candleBody(sf::Vector2f(width, std::abs(openPos - closePos)));
        candleBody.setPosition(50.0f, openPos < closePos ? closePos : openPos);
        candleBody.setFillColor(open > close ? sf::Color::Red : sf::Color::Green);

        // Create the wick (line for high/low)
        sf::RectangleShape candleWick(sf::Vector2f(2.0f, std::abs(highPos - lowPos)));
        candleWick.setPosition(55.0f, lowPos);
        candleWick.setFillColor(sf::Color::White);

        // Add the shapes to the vector
        candlesticks.push_back(candleBody);
        candlesticks.push_back(candleWick);

        // Move to the next candlestick position (increment by width + spacing)
        width += 40.0f;  // Adjust spacing between candlesticks
    }

    // Main SFML loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        for (const auto& candle : candlesticks) {
            window.draw(candle);
        }
        window.display();
    }
    return 0;
}