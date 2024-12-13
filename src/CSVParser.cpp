#include "../include/CSVParser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

double parseCurrency(const std::string& str) {
    std::string cleanStr = str;
    cleanStr.erase(std::remove(cleanStr.begin(), cleanStr.end(), '$'), cleanStr.end());

    try {
        return std::stod(cleanStr);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing currency: " << str << std::endl;
        return 0.0;
    }
}

bool CSVParser::parseCSV(const std::string& filename, std::vector<Candlestick>& candlesticks) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return false;
    }

    std::string line;
    bool isFirstLine = true;

    while (std::getline(file, line)) {
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }

        std::stringstream ss(line);
        std::string date, closeStr, volumeStr, openStr, highStr, lowStr;

        // Read the CSV values, split by commas
        std::getline(ss, date, ',');           // Date
        std::getline(ss, closeStr, ',');       // Close/Last
        std::getline(ss, volumeStr, ',');      // Volume (not used for now)
        std::getline(ss, openStr, ',');        // Open
        std::getline(ss, highStr, ',');        // High
        std::getline(ss, lowStr, ',');         // Low

        // Convert the string data to appropriate types
        try {
            double open = parseCurrency(openStr);
            double high = parseCurrency(highStr);
            double low = parseCurrency(lowStr);
            double close = parseCurrency(closeStr);

            Candlestick candle(date, open, high, low, close);
            candlesticks.push_back(candle);
        } catch (const std::exception& e) {
            std::cerr << "Error: Could not parse data in line: " << line << "\n" << e.what() << std::endl;
            continue;
        }
    }

    file.close();
    return true;
}