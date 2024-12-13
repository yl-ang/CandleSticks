#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <vector>
#include "Candlestick.h"

class CSVParser {
public:
    static bool parseCSV(const std::string& filename, std::vector<Candlestick>& candlesticks);
};

#endif // CSV_PARSER_H
