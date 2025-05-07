#include "../include/Common.h"
#include "../include/Constants.h"

bool operator==(const Coordinate& c1, const Coordinate& c2) {
    return (c1.first == c2.first && c1.second == c2.second);
}

bool inBoard(const Coordinate &location) {
    char coll = location.second;
    int row = location.first;
    return (coll >= FIRST_COLL &&
            coll <= LAST_COLL &&
            row >= FIRST_ROW &&
            row <= LAST_ROW);
}

COLOR colorNot(COLOR color) {
    return (color == WHITE) ? BLACK : WHITE;
}

Coordinate flipChessCoord(const Coordinate& coord) {
    char coll = static_cast<char>('a' + (coord.first - 1)); // Converts numeric row to char column
    int row = static_cast<int>(tolower(coord.second) - 'a' + 1); // Converts char column to numeric row
    return {row, coll}; // Returns a flipped coordinate
}

std::ostream &operator<<(std::ostream &os, const Move &mv) {
    os << flipChessCoord(mv._source).second << flipChessCoord(mv._source).first << " " <<
    flipChessCoord(mv._destination).second << flipChessCoord(mv._destination).first << std::endl;
    return os;
}
