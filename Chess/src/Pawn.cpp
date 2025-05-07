#include "../include/Pawn.h"
#include "../include/Move.h"
#include "../include/Pieces.h"
#include "../include/Queen.h"
#include "../include/Bishop.h"
#include "../include/Rook.h"
#include "../include/Constants.h"
#include "../include/MyExceptions.h"

Pawn::Pawn(COLOR color,const Coordinate& location): Piece(PAWN , color , location),promotedPiece(nullptr) {}

std::vector<Coordinate> Pawn::getRawMoves(const Pieces &board) {
    std::vector<Coordinate> result;

    // Check if the Pawn hasn't moved yet
    if (!isHasMoved()) {
        // Check for the first and second square in front of the Pawn
        if (!frontFreeBoxes(board, *this).empty() && !board.isOccupiedBox(frontFreeBoxes(board, *this).at(0))) {
            result.push_back(frontFreeBoxes(board, *this).at(0));
        }
        if (frontFreeBoxes(board, *this).size() > 1 && !board.isOccupiedBox(frontFreeBoxes(board, *this).at(1))) {
            result.push_back(frontFreeBoxes(board, *this).at(1));
        }
    } else {
        // If Pawn has moved, check only the first square in front
        if (!frontFreeBoxes(board, *this).empty() && !board.isOccupiedBox(frontFreeBoxes(board, *this).at(0))) {
            result.push_back(frontFreeBoxes(board, *this).at(0));
        }
    }

    // Check diagonal captures (right and left)
    if (!diagFrontRight(board, *this).empty()) {
        Coordinate rightDiag = diagFrontRight(board, *this).at(0);
        if (board.isOccupiedBox(rightDiag) && board.getPiece(rightDiag)->getColor() != getColor()) {
            result.push_back(rightDiag);
        }
    }
    if (!diagFrontLeft(board, *this).empty()) {
        Coordinate leftDiag = diagFrontLeft(board, *this).at(0);
        if (board.isOccupiedBox(leftDiag) && board.getPiece(leftDiag)->getColor() != getColor()) {
            result.push_back(leftDiag);
        }
    }

    return result;
}


const std::shared_ptr<Piece> &Pawn::getPromotedPiece() const {
    return promotedPiece;
}


void Pawn::userPromotionChoice(const Coordinate & promotionLocation) {
    bool correctInput = false;
    std::string choice;

    // Choose the promoted piece based on user input
    while (!correctInput) {
        std::cout << "This pawn can be promoted, choose promotion type:\n";
        std::cout << "Press (1) for Queen.\n";
        std::cout << "Press (2) for Rook.\n";
        std::cout << "Press (3) for Bishop.\n";
        std::cout << "Press (4) for Knight.\n";
        std::cin >> choice;

        if (choice == "1") {
            promotedPiece = std::make_shared<Queen>(getColor() , promotionLocation);
            correctInput = true;
        } else if (choice == "2") {
            promotedPiece = std::make_shared<Rook>(getColor() , promotionLocation);
            correctInput = true;
        } else if (choice == "3") {
            promotedPiece = std::make_shared<Bishop>(getColor() , promotionLocation);
            correctInput = true;
        } else if (choice == "4") {
            promotedPiece = std::make_shared<Knight>(getColor() , promotionLocation);
            correctInput = true;
        } else {
            // Throw error if invalid input is entered
            throw WrongPromotionInput(choice + " is no a legal choice");
        }
    }

    // Check if the promotion was successful and the piece is valid
    if (!promotedPiece) {
        throw std::runtime_error("Promotion failed: piece is null.");
    }

}

bool Pawn::canPromote() {
    if (getColor() == WHITE){
        return  static_cast<char>(getLocation().first + 1) == LAST_ROW;
    }
    else{
        return static_cast<char>(getLocation().first - 1) == FIRST_ROW;
       }
}

std::shared_ptr<Piece> Pawn::clone() const {
    return std::make_shared<Pawn>(*this);
}

