#ifndef CANDLESTICK_H
#define CANDLESTICK_H

#include <string>
#include <ctime>

class Candlestick {
public:
    Candlestick(const std::tm& timestamp, double open, double high, double low, double close);

    const std::tm& getTimestamp() const;
    double getOpen() const;
    double getHigh() const;
    double getLow() const;
    double getClose() const;

    bool operator<(const Candlestick& other) const;

private:
    std::tm timestamp;  // Store timestamp as std::tm
    double open;        // Opening price
    double high;        // Highest price during the period
    double low;         // Lowest price during the period
    double close;       // Closing price
};

#endif // CANDLESTICK_H