#ifndef CANDLESTICK_H
#define CANDLESTICK_H

#include <string>

class Candlestick {
public:
    Candlestick(const std::string& timestamp, double open, double high, double low, double close);

    std::string getTimestamp() const;
    double getOpen() const;
    double getHigh() const;
    double getLow() const;
    double getClose() const;

private:
    std::string timestamp;  // Timestamp for the candlestick (e.g., "2024-12-12T09:00:00Z")
    double open;            // Opening price
    double high;            // Highest price during the period
    double low;             // Lowest price during the period
    double close;           // Closing price
};

#endif // CANDLESTICK_H
