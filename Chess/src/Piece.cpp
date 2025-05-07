#include "../include/Piece.h"
#include <utility>
#include "../include/Pieces.h"

Piece::Piece(ID id, COLOR color,Coordinate  location): _id(id) , _color(color) , _location(std::move(location)){
    _hasMoved = false;
    _isProtected = false;
}

void Piece::addMoves(std::vector<Coordinate> moves) {
    if(getId() == KING){
        clearMoves();
    }
    _potenMoves.insert(moves.begin() , moves.end());
}

void Piece::clearMoves() {
    _potenMoves.clear();
}

bool Piece::isValidMove(Coordinate move , const Pieces& board) {
    std::vector<Coordinate> raw = getRawMoves(board);
    for(auto coord: raw)if(coord == move)return true;
    return false;
}

void Piece::updatePotenMoves(const Pieces & board) {
    clearMoves();
    addMoves(removeOwnCheck(board));
}

std::vector<Coordinate> Piece::removeOwnCheck(const Pieces &board) {
    std::vector<Coordinate> result = getRawMoves(board);
    for (auto it = result.begin(); it != result.end();){
        Coordinate currentMove = *it;
        Pieces currentBoard(board);

        if(currentBoard.isOccupiedBox(currentMove) && getId() == KING && board.getPiece(currentMove)->isIsProtected()){
            it = result.erase(it);
            continue;
        }
        currentBoard.pieceMove(currentMove,clone());
        std::set<Coordinate> temp = currentBoard.getPiecesRawMoves(colorNot(getColor()));
        if (temp.find(currentBoard.getKingLocation(getColor())) != temp.end()){
            it = result.erase(it);
        }
        else{
            ++it;
        }
    }
    return result;
}

bool Piece::willBeInCheck(const Coordinate& destination, const Pieces &board) const {
    Pieces currentBoard(board);

    currentBoard.pieceMove(destination, clone());

    std::set<Coordinate> opponentMoves = currentBoard.getPiecesRawMoves(colorNot(getColor()));
    Coordinate kingLocation = currentBoard.getKingLocation(getColor());

    return opponentMoves.find(kingLocation) != opponentMoves.end();
}
