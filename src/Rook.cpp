#include "Rook.h"
#include "Move.h"

Rook::Rook(COLOR color,const Coordinate& location) : Piece(ROOK, color, location) {}

std::vector<Coordinate> Rook::getRawMoves(const Pieces &board) {
    std::vector<Coordinate> result;
    // Get all free spaces in the possible directions
    std::vector<Coordinate> tmp = frontFreeBoxes(board, *this);
    result.insert(result.end(), tmp.begin(), tmp.end());

    tmp = backFreeBoxes(board, *this);
    result.insert(result.end(), tmp.begin(), tmp.end());

    tmp = rightFreeBoxes(board, *this);
    result.insert(result.end(), tmp.begin(), tmp.end());

    tmp = leftFreeBoxes(board, *this);
    result.insert(result.end(), tmp.begin(), tmp.end());

    return result;
}

std::shared_ptr<Piece> Rook::clone() const {
    return std::make_shared<Rook>(*this);
}
