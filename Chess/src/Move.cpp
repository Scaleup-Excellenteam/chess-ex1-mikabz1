#include "../include/Move.h"
#include "../include/Knight.h"

bool isSameColor(const Pieces &board,const Coordinate& location, COLOR color) {
    return board.getPiece(location)->getColor() == color;
}

std::vector<Coordinate> frontFreeBoxes(const Pieces &board, const Piece &piece) {
    bool searchEnd = false;
    int direction = (piece.getColor() == BLACK) ? -1 : 1;
    int moveLength = direction;
    int row = piece.getLocation().first;
    char coll = piece.getLocation().second;
    std::vector<Coordinate> result;
    while(!searchEnd){
        Coordinate checkFree(row+moveLength , coll);
        if(!inBoard(checkFree))break;
        if(!board.isOccupiedBox(checkFree)){
            result.push_back(checkFree);
        }
        else{
            if(!isSameColor(board,checkFree,piece.getColor())){
                result.push_back(checkFree);
            }
            else{
                board.getPiece(checkFree)->setIsProtected(true);
            }
            searchEnd = true;
        }
        moveLength += direction;
        if(piece.getId() == KING){
            searchEnd = true;
        }
    }
    return result;
}

std::vector<Coordinate> backFreeBoxes(const Pieces &board, const Piece &piece) {
    bool searchEnd = false;
    int direction = (piece.getColor() == WHITE) ? -1 : 1;
    int moveLength = direction;
    int row = piece.getLocation().first;
    char coll = piece.getLocation().second;
    std::vector<Coordinate> result;
    while(!searchEnd){
        Coordinate checkFree(row+moveLength , coll);
        if(!inBoard(checkFree))break;
        if(!board.isOccupiedBox(checkFree)){
            result.push_back(checkFree);
        }
        else{
            if(!isSameColor(board,checkFree,piece.getColor())){
                result.push_back(checkFree);
            }
            else{
                board.getPiece(checkFree)->setIsProtected(true);
            }
            searchEnd = true;
        }
        moveLength += direction;
        if(piece.getId() == KING){
            searchEnd = true;
        }
    }
    return result;
}

std::vector<Coordinate> rightFreeBoxes(const Pieces &board, const Piece &piece) {
    bool searchEnd = false;
    int direction = 1;
    int row = piece.getLocation().first;
    char coll = piece.getLocation().second;
    std::vector<Coordinate> result;
    while(!searchEnd){
        Coordinate checkFree(row ,coll+direction);
        if(!inBoard(checkFree))break;
        if(!board.isOccupiedBox(checkFree)){
            result.push_back(checkFree);
        }
        else{
            if(!isSameColor(board,checkFree,piece.getColor())){
                result.push_back(checkFree);
            }
            else{
                board.getPiece(checkFree)->setIsProtected(true);
            }
            searchEnd = true;
        }
        direction++;
        if(piece.getId() == KING){
            searchEnd = true;
        }
    }
    return result;
}

std::vector<Coordinate> leftFreeBoxes(const Pieces &board, const Piece &piece) {
    bool searchEnd = false;
    int direction = -1;
    int row = piece.getLocation().first;
    char coll = piece.getLocation().second;
    std::vector<Coordinate> result;
    while(!searchEnd){
        Coordinate checkFree(row , coll+direction);
        if(!inBoard(checkFree))break;
        if(!board.isOccupiedBox(checkFree)){
            result.push_back(checkFree);
        }
        else{
            if(!isSameColor(board,checkFree,piece.getColor())){
                result.push_back(checkFree);
            }
            else{
                board.getPiece(checkFree)->setIsProtected(true);
            }
            searchEnd = true;
        }
        direction--;
        if(piece.getId() == KING){
            searchEnd = true;
        }
    }
    return result;
}

std::vector<Coordinate> diagFrontRight(const Pieces &board, const Piece &piece) {
    bool searchEnd = false;
    int direction = (piece.getColor() == BLACK) ? -1 :  1;
    int moveLength = direction;
    int row = piece.getLocation().first;
    char coll = piece.getLocation().second;
    std::vector<Coordinate> result;
    while(!searchEnd){
        Coordinate checkFree(row + moveLength , coll+moveLength);
        if(!inBoard(checkFree))break;
        if(!board.isOccupiedBox(checkFree)){
            result.push_back(checkFree);
        }
        else{
            if(!isSameColor(board,checkFree,piece.getColor())){
                result.push_back(checkFree);
            }
            else{
                board.getPiece(checkFree)->setIsProtected(true);
            }
            searchEnd = true;
        }
        moveLength += direction;
        if(piece.getId() == KING){
            searchEnd = true;
        }
    }
    return result;
}

std::vector<Coordinate> diagBackRight(const Pieces &board, const Piece &piece) {
    bool searchEnd = false;
    int rowDirection = (piece.getColor() == WHITE) ? -1 :  1;
    int collDirection = -1*rowDirection;
    int collLength = collDirection;
    int rowLength = rowDirection;
    int row = piece.getLocation().first;
    char coll = piece.getLocation().second;
    std::vector<Coordinate> result;
    while(!searchEnd){
        Coordinate checkFree(row + rowLength , coll+collLength);
        if(!inBoard(checkFree))break;
        if(!board.isOccupiedBox(checkFree)){
            result.push_back(checkFree);
        }
        else{
            if(!isSameColor(board,checkFree,piece.getColor())){
                result.push_back(checkFree);
            }
            else{
                board.getPiece(checkFree)->setIsProtected(true);
            }
            searchEnd = true;
        }
        collLength += collDirection;
        rowLength += rowDirection;
        if(piece.getId() == KING){
            searchEnd = true;
        }
    }
    return result;
}

std::vector<Coordinate> diagFrontLeft(const Pieces &board, const Piece &piece) {
    bool searchEnd = false;
    int rowDirection = (piece.getColor() == BLACK) ? -1 :  1;
    int collDirection = -1*rowDirection;
    int collLength = collDirection;
    int rowLength = rowDirection;
    int row = piece.getLocation().first;
    char coll = piece.getLocation().second;
    std::vector<Coordinate> result;
    while (!searchEnd){
        Coordinate checkFree(row+rowLength , coll + collLength);
        if(!inBoard(checkFree))break;
        if(!board.isOccupiedBox(checkFree)){
            result.push_back(checkFree);
        }
        else{
            //is in this box is filled with opposite piece then add the option to eat it , else make this box protected.
            if(!isSameColor(board,checkFree,piece.getColor())){
                result.push_back(checkFree);
            }
            else {
                board.getPiece(checkFree)->setIsProtected(true);
            }
            searchEnd = true;
        }
        collLength += collDirection;
        rowLength += rowDirection;
        if(piece.getId() == KING){
            searchEnd = true;
        }
    }
    return result;
}

std::vector<Coordinate> diagBackLeft(const Pieces &board, const Piece &piece) {
    bool searchEnd = false;
    int direction = (piece.getColor() == WHITE) ? -1 :  1;
    int moveLength = direction;
    int row = piece.getLocation().first;
    char coll = piece.getLocation().second;
    std::vector<Coordinate> result;
    while (!searchEnd){
        Coordinate checkFree( row+moveLength , coll + moveLength);
        if(!inBoard(checkFree))break;
        if(!board.isOccupiedBox(checkFree)){
            result.push_back(checkFree);
        }
        else{
            //is in this box is filled with opposite piece then add the option to eat it , else make this box protected.
            if(!isSameColor(board,checkFree,piece.getColor())){
                result.push_back(checkFree);
            }
            else {
                board.getPiece(checkFree)->setIsProtected(true);
            }
            searchEnd = true;
        }
        moveLength += direction;
        if(piece.getId() == KING){
            searchEnd = true;
        }
    }
    return result;
}

std::vector<Coordinate> frontKnight(const Pieces &board, const Knight &knight) {
    std::vector<Coordinate> result;
    int row = knight.getLocation().first;
    char coll = knight.getLocation().second;
    int direction = (knight.getColor() == WHITE) ? 2 : -2;
    Coordinate checkRight(row + direction , coll + 1);
    Coordinate checkLeft( row + direction , coll - 1);
    std::vector<Coordinate> help;
    help.push_back(checkRight);
    help.push_back(checkLeft);
    for(Coordinate coord : help){
        if(inBoard(coord)){
            if(!board.isOccupiedBox(coord)){
                result.push_back(coord);
            }
            else {
                //is in this coord is filled with opposite piece then add the option to eat it , else make this coord protected.
                if (!isSameColor(board, coord, knight.getColor())){
                    result.push_back(coord);
                }
                else {
                    board.getPiece(coord)->setIsProtected(true);
                }
            }
        }
    }
    return result;
}

std::vector<Coordinate> backKnight(const Pieces &board, const Knight &knight) {
    std::vector<Coordinate> result;
    int row = knight.getLocation().first;
    char coll = knight.getLocation().second;
    int direction = (knight.getColor() == BLACK) ? 2 : -2;
    Coordinate checkRight(row + direction , coll + 1);
    Coordinate checkLeft(row + direction , coll - 1);
    std::vector<Coordinate> help;
    help.push_back(checkRight);
    help.push_back(checkLeft);
    for(Coordinate coord : help){
        if(inBoard(coord)){
            if(!board.isOccupiedBox(coord)){
                result.push_back(coord);
            }
            else {
                //is in this coord is filled with opposite piece then add the option to eat it , else make this coord protected.
                if (!isSameColor(board, coord, knight.getColor())){
                    result.push_back(coord);
                }
                else {
                    board.getPiece(coord)->setIsProtected(true);
                }
            }
        }
    }
    return result;
}

std::vector<Coordinate> rightKnight(const Pieces &board, const Knight &knight) {
    std::vector<Coordinate> result;
    int row = knight.getLocation().first;
    char coll = knight.getLocation().second;
    int direction = (knight.getColor() == WHITE) ? 2 : -2;
    Coordinate checkRight(row + 1 , coll + direction);
    Coordinate checkLeft(row -1 , coll + direction);
    std::vector<Coordinate> help;
    help.push_back(checkRight);
    help.push_back(checkLeft);
    for(Coordinate coord : help){
        if(inBoard(coord)){
            if(!board.isOccupiedBox(coord)){
                result.push_back(coord);
            }
            else {
                //is in this coord is filled with opposite piece then add the option to eat it , else make this coord protected.
                if (!isSameColor(board, coord, knight.getColor())){
                    result.push_back(coord);
                }
                else{
                    board.getPiece(coord)->setIsProtected(true);
                }
            }
        }
    }
    return result;
}

std::vector<Coordinate> leftKnight(const Pieces &board, const Knight &knight) {
    std::vector<Coordinate> result;
    int row = knight.getLocation().first;
    char coll = knight.getLocation().second;
    int direction = (knight.getColor() == BLACK) ? 2 : -2;
    Coordinate checkRight(row + 1 , coll + direction);
    Coordinate checkLeft(row -1 , coll + direction);
    std::vector<Coordinate> help;
    help.push_back(checkRight);
    help.push_back(checkLeft);
    for(Coordinate coord : help){
        if(inBoard(coord)){
            if(!board.isOccupiedBox(coord)){
                result.push_back(coord);
            }
            else {
                //is in this coord is filled with opposite piece then add the option to eat it , else make this coord protected.
                if (!isSameColor(board, coord, knight.getColor())){
                    result.push_back(coord);
                }
                else{
                    board.getPiece(coord)->setIsProtected(true);
                }
            }
        }
    }
    return result;
}

std::pair<Coordinate, Coordinate> stringToCoordinate(const std::string& str) {
    return {{str[1] - '0', toupper(str[0])} , {str[3] - '0',toupper(str[2])}};
}
