#include "../include/Candlestick.h"
#include <ctime>

Candlestick::Candlestick(const std::tm& timestamp, double open, double high, double low, double close)
    : timestamp(timestamp), open(open), high(high), low(low), close(close) {}

const std::tm& Candlestick::getTimestamp() const {
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

bool Candlestick::operator<(const Candlestick& other) const {
    return std::difftime(std::mktime(const_cast<std::tm*>(&timestamp)),
                         std::mktime(const_cast<std::tm*>(&other.timestamp))) < 0;
}