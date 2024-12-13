#include "../include/Candlestick.h"

Candlestick::Candlestick(const std::string& timestamp, double open, double high, double low, double close)
    : timestamp(timestamp), open(open), high(high), low(low), close(close) {}

std::string Candlestick::getTimestamp() const {
    return timestamp;
}

double Candlestick::getOpen() const {
    return open;
}

double Candlestick::getHigh() const {
    return high;
}

double Candlestick::getLow() const {
    return low;
}

double Candlestick::getClose() const {
    return close;
}