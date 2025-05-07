#include "Pieces.h"
#include "Constants.h"
#include "Rook.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include "Bishop.h"
#include "MyExceptions.h"

Pieces::Pieces(const std::string &str) {
    if (str.size() != BOARD_CELL_NUMBER) {
        std::cerr << "Invalid board string length: expected " << BOARD_CELL_NUMBER
                  << ", got " << str.size() << std::endl;
        throw std::runtime_error("Invalid board string length: " + str);
    }

    for(int i = 0; i < BOARD_CELL_NUMBER;i++){
        int row = (i / ROW_SIZE) + 1;
        int col = i % ROW_SIZE;
        Coordinate location = {row , FIRST_COLL + col};
        switch (str[i]) {
            case 'r': _board[location] = std::make_shared<Rook>(BLACK ,location); break;
            case 'R': _board[location] = std::make_shared<Rook>(WHITE ,location); break;
            case 'n': _board[location] = std::make_shared<Knight>(BLACK ,location); break;
            case 'N': _board[location] = std::make_shared<Knight>(WHITE ,location); break;
            case 'b': _board[location] = std::make_shared<Bishop>(BLACK ,location); break;
            case 'B': _board[location] = std::make_shared<Bishop>(WHITE ,location); break;
            case 'k': _board[location] = std::make_shared<King>(BLACK ,location); break;
            case 'K': _board[location] = std::make_shared<King>(WHITE ,location); break;
            case 'q': _board[location] = std::make_shared<Queen>(BLACK ,location); break;
            case 'Q': _board[location] = std::make_shared<Queen>(WHITE ,location); break;
            case 'p': _board[location] = std::make_shared<Pawn>(BLACK ,location); break;
            case 'P': _board[location] = std::make_shared<Pawn>(WHITE ,location); break;
            case '#': break;
            default:
                std::cerr << "Invalid character '" << str[i] << "' at index " << i << std::endl;
                throw std::runtime_error("Invalid character in board string: " + str);
        }
    }
}
Pieces::Pieces(const Pieces &board) {
    for(const auto& element : board._board){
        _board[element.first] = element.second->clone();
    }
}

 bool Pieces::isOccupiedBox(const Coordinate& location) const {
    return _board.find(location) != _board.end();
}

void Pieces::addPiece(const std::shared_ptr<Piece>& piece){
    if(piece == nullptr){
        throw NullPiece("FATAL ERROR: cannot add null piece to the board");
    }
    _board[piece->getLocation()] = piece;
}

void Pieces::removePiece(const Coordinate& location) {
    if(isOccupiedBox(location)){
        _board.erase(location);
    }
}

Coordinate Pieces::getKingLocation(COLOR color) const {
    for(auto &piece : _board){
        if(piece.second->getId() == KING && piece.second->getColor() == color){
            return piece.second->getLocation();
        }
    }
    return {ROW_PLACE_HOLDER , COLL_PLACE_HOLDER};
}

const std::shared_ptr<Piece>& Pieces::getPiece(const Coordinate& location)const{
    static const std::shared_ptr<Piece> nullPiece = nullptr;
    if(_board.find(location) == _board.end()){
        return nullPiece;
    }
    return _board.at(location);
}

std::set<Coordinate> Pieces::getPiecesPotenMoves(COLOR color) {
    std::set<Coordinate> result;
    for(auto &element : _board){
        if(element.second->getColor() == color){
            auto temp = element.second->getPotenMoves();
            result.insert(temp.begin() , temp.end());
        }
    }
    return result;
}

std::set<Coordinate> Pieces::getPiecesRawMoves(COLOR color) {
    std::set<Coordinate> result;
    for(auto &element : _board){
        if(element.second->getColor() == color){
            auto temp = element.second->getRawMoves(*this);
            result.insert(temp.begin() , temp.end());
        }
    }
    return result;
}

bool Pieces::isCheck(COLOR color) {
    return getPiecesPotenMoves(colorNot(color)).contains(getKingLocation(color));

}

void Pieces::pieceMove(const Coordinate& destination,const std::shared_ptr<Piece>& piece){
    Coordinate currentLocation = piece->getLocation();
    piece->setLocation(destination);
    piece->setHasMoved(true);
    addPiece(piece);
    removePiece(currentLocation);
}

void Pieces::updatePotenMoves(COLOR color) {
    for(auto &element : _board){
        element.second->setIsProtected(false);
    }
    for(const auto& element : _board){
        if(element.second->getColor() != color){
            element.second->updatePotenMoves(*this);
        }
    }
    for(auto &element : _board){
        if(element.second->getColor() == color){
            element.second->updatePotenMoves(*this);
        }
    }
}


std::vector<Move> Pieces::getAllLegalMoves(COLOR color)const{
    std::vector<Move> result;
    
    for(const auto& [coord, piece] : _board){
        if(piece->getColor() != color)continue;
        // Retrieve potential moves for the piece
        for(const auto& destination : piece->getPotenMoves()){
            result.push_back({coord , destination , 0});
        }
    }
    return result;
}

void Pieces::makeMove(const Coordinate & destination,const std::shared_ptr<Piece>& piece) {
    auto pieceToMove = piece;
    if (piece->getId() == PAWN){
        auto pawn = std::dynamic_pointer_cast<Pawn>(piece);
        if (pawn->canPromote() && pawn){
            try {
                pawn->userPromotionChoice(pawn->getLocation());
                pieceToMove = pawn->getPromotedPiece();
                addPiece(pieceToMove);
            }
            catch (WrongPromotionInput& e){
                std::cout << e.what();
            }


        }
    }
    pieceMove(destination,pieceToMove);
}







