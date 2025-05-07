#include "Knight.h"
#include "Move.h"

Knight::Knight(COLOR color, const Coordinate& location) : Piece(KNIGHT, color, location) {}

std::vector<Coordinate> Knight::getRawMoves(const Pieces &board) {
    std::vector<Coordinate> result;
    
    std::vector<Coordinate> tmp = frontKnight(board, *this);
    result.insert(result.end(), tmp.begin(), tmp.end());

    tmp = backKnight(board, *this);
    result.insert(result.end(), tmp.begin(), tmp.end());

    tmp = rightKnight(board, *this);
    result.insert(result.end(), tmp.begin(), tmp.end());

    tmp = leftKnight(board, *this);
    result.insert(result.end(), tmp.begin(), tmp.end());

    return result; 
}

std::shared_ptr<Piece> Knight::clone() const {
    return std::make_shared<Knight>(*this); 
}
