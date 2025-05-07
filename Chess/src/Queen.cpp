#include "../include/Queen.h"
#include "../include/Move.h"


Queen::Queen(COLOR color,const Coordinate& location) : Piece(QUEEN, color, location) {}

std::vector<Coordinate> Queen::getRawMoves(const Pieces &board) {
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

    tmp = diagFrontRight(board, *this);
    result.insert(result.end(), tmp.begin(), tmp.end());

    tmp = diagFrontLeft(board, *this);
    result.insert(result.end(), tmp.begin(),tmp.end());

    tmp = diagBackRight(board, *this);
    result.insert(result.end(), tmp.begin(), tmp.end());

    tmp = diagBackLeft(board, *this);
    result.insert(result.end(), tmp.begin(), tmp.end());

    return result;
}

std::shared_ptr<Piece> Queen::clone() const {
    return std::make_shared<Queen>(*this);
}
