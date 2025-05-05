#include "Pawn.h"
#include "Move.h"
#include "Pieces.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "Constants.h"
#include "MyExceptions.h"

/**
 * @brief Constructs a Pawn object.
 * Initializes a Pawn with the specified color and location on the chessboard.
 * @param color The color of the Pawn (either WHITE or BLACK).
 * @param location The initial location of the Pawn on the board.
 */
Pawn::Pawn(COLOR color,const Coordinate& location): Piece(PAWN , color , location),promotedPiece(nullptr) {}
/**
 * @brief Returns all valid moves for the Pawn.
 * Calculates the Pawn's potential moves based on its current position and whether it has moved before. The function
 * checks for possible forward moves and diagonal captures.
 * @param board The current chessboard state.
 * @return A vector of coordinates representing the valid moves for the Pawn.
 */
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

/// @brief Retrieves the promoted piece of the pawn, if it has been promoted.
/// @return A constant reference to the shared pointer of the promoted piece.
const std::shared_ptr<Piece> &Pawn::getPromotedPiece() const {
    return promotedPiece;
}

/// @brief Handles user input for promoting the pawn to another piece (Queen, Rook, Bishop, or Knight).
/// @param promotionLocation The coordinate where the promotion is taking place.
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
/// @brief Checks if the pawn is eligible for promotion based on its current location and color.
/// @return True if the pawn can be promoted (i.e., it has reached the last row for white or first row for black).
bool Pawn::canPromote() {
    if (getColor() == WHITE){
        // White pawn can promote when it reaches the last row
        return  static_cast<char>(getLocation().first + 1) == LAST_ROW;
    }
    else{
        // Black pawn can promote when it reaches the first row
        return static_cast<char>(getLocation().first - 1) == FIRST_ROW;
       }
}

/**
 * @brief Creates a clone of the Pawn.
 * Returns a new shared pointer to a copy of the current Pawn.
 * @return A shared pointer to the cloned Pawn.
 */
std::shared_ptr<Piece> Pawn::clone() const {
    return std::make_shared<Pawn>(*this);
}

