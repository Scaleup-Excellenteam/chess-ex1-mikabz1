#include "../include/King.h"

King::King(COLOR color, const Coordinate& location) : Piece(KING, color, location) {}

std::vector<Coordinate> King::getRawMoves(const Pieces &board) {
    std::vector<Coordinate> result;

    std::vector<Coordinate> temp = diagFrontRight(board, *this);
    if (!temp.empty()) {
        result.push_back(temp.at(0)); 
    }

    temp = diagFrontLeft(board, *this);
    if (!temp.empty()) {
        result.push_back(temp.at(0)); 
    }

    temp = diagBackRight(board, *this);
    if (!temp.empty()) {
        result.push_back(temp.at(0));  
    }

    temp = diagBackLeft(board, *this);
    if (!temp.empty()) {
        result.push_back(temp.at(0));  
    }

    temp = frontFreeBoxes(board, *this);
    if (!temp.empty()) {
        result.push_back(temp.at(0));  
    }

    temp = backFreeBoxes(board, *this);
    if (!temp.empty()) {
        result.push_back(temp.at(0)); 
    }

    temp = rightFreeBoxes(board, *this);
    if (!temp.empty()) {
        result.push_back(temp.at(0));  
    }

    temp = leftFreeBoxes(board, *this);
    if (!temp.empty()) {
        result.push_back(temp.at(0)); 
    }

    return result;  
}

std::shared_ptr<Piece> King::clone() const {
    return std::make_shared<King>(*this); 
}
