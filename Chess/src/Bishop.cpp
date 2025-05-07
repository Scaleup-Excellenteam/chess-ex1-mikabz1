#include "../include/Bishop.h"
#include "../include/Move.h"

Bishop::Bishop(COLOR color, const Coordinate& location) : Piece(BISHOP, color, location) {

}


std::vector<Coordinate> Bishop::getRawMoves(const Pieces &board) {
    std::vector<Coordinate> result;

    std::vector<Coordinate> temp = diagFrontRight(board, *this);
    result.insert(result.end(), temp.begin(), temp.end());
    
    temp = diagFrontLeft(board, *this);
    result.insert(result.end(), temp.begin(), temp.end());

    temp = diagBackRight(board, *this);
    result.insert(result.end(), temp.begin(), temp.end());

    temp = diagBackLeft(board, *this);
    result.insert(result.end(), temp.begin(), temp.end());

    return result;
}

std::shared_ptr<Piece> Bishop::clone() const {
    return std::make_shared<Bishop>(*this);
}
