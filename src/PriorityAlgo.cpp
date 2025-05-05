#include "PriorityAlgo.h"
#include "Constants.h"
#include <vector>
#include <climits>
#include "MyExceptions.h"
#include "Constants.h"

/**
* @brief Returns the score of a piece based on its type.
* @param id The ID of the piece.
* @return An integer representing the score of the piece.
*/
 int pieceScore(ID id) {
    switch (id) {
        case KING:   return 100;
        case QUEEN:  return 90;
        case ROOK:   return 50;
        case KNIGHT:
        case BISHOP: return 30;
        case PAWN:   return 10;
        default: return 0;
    }
}
/**
* @brief Calculates the minimum threat score for a given coordinate.
* @param color The color of the player whose moves are being evaluated.
* @param coordinate The coordinate of the piece being evaluated.
* @param board The current state of the board.
* @return The minimum threat score considering opponent's pieces that can threaten the given coordinate.
*/
 int getMinThreatScore(COLOR color, Coordinate coordinate,Pieces &board) {
    //**********add special exception********************
    int result = 0;
    board.updatePotenMoves(colorNot(color));
    int currentPieceScore = pieceScore(board.getPiece(coordinate)->getId());
    for (int i = FIRST_ROW; i < LAST_ROW; ++i) {
        for (char j = FIRST_COLL; j < LAST_COLL; ++j) {
            auto currentPiece = board.getPiece({i , j});
            if(currentPiece == nullptr)continue;
            auto potenMoves = currentPiece->getPotenMoves();
            int score = pieceScore(currentPiece->getId());
            if(potenMoves.find(coordinate) != potenMoves.end() && currentPiece->getColor() != color && score < currentPieceScore){
                result += score;
            }
        }
    }
    return result;
}
/**
* @brief Calculates the maximum threat score for a given coordinate.
* @param color The color of the player whose moves are being evaluated.
* @param coordinate The coordinate of the piece being evaluated.
* @param board The current state of the board.
* @return The maximum threat score considering the player's own pieces that could move to the given coordinate.
*/
 int getMaxThreatScore(COLOR color, Coordinate coordinate,Pieces &board) {
    //**********add special exception**********************
    int result = 0;
    board.updatePotenMoves(color);
    int currentPieceScore = pieceScore(board.getPiece(coordinate)->getId());
    auto potenMoves = board.getPiece(coordinate)->getPotenMoves();
    for(const auto& coord : potenMoves){
        const auto& currentPiece = board.getPiece(coord);
        if(currentPiece == nullptr)continue;
        int score = pieceScore(currentPiece->getId());
        if(currentPieceScore < score){
            result += score;
        }
    }
    return result;
}
/**
* @brief Executes the main algorithm for determining the best move for the AI using minimax with alpha-beta pruning.
* @param depth The depth of the search tree.
* @param color The color of the player whose turn it is.
* @param board The current state of the board.
* @return A priority queue of moves, sorted by their evaluation scores.
*/
 PriorityQueue<Move> mainAlgo(int depth, COLOR color,Pieces &board) {
    PriorityQueue<Move> priorityQueue;
    auto legalMoves = board.getAllLegalMoves(color);

    for(auto move : legalMoves){
        auto destinationPiece = board.getPiece(move._destination);
        if (destinationPiece){
            destinationPiece = destinationPiece->clone();
        }
        auto sourcePiece = board.getPiece(move._source)->clone();
        move._score = minimax(depth, move, board, color, color, INT_MIN, INT_MAX);
        undoMove(move,board,sourcePiece,destinationPiece);
        priorityQueue.push(move);
    }
    return priorityQueue;
}
/**
* @brief The recursive minimax algorithm with alpha-beta pruning to evaluate the best move.
* @param depth The depth of the search tree.
* @param move The current move being evaluated.
* @param board The current state of the board.
* @param maximizing The color of the player maximizing the score.
* @param currentColor The current color of the player whose turn it is.
* @param alpha The alpha value for alpha-beta pruning.
* @param beta The beta value for alpha-beta pruning.
* @return The evaluated score for the current move.
*/
 int minimax(int depth, Move move, Pieces& board, COLOR maximizing, COLOR currentColor, int alpha, int beta) {
    if (depth <= 0) return move._score;// Base case: return score for leaf node

    // Simulate the move and evaluate its score
    auto& destPiece = board.getPiece(move._destination);
    auto movingPiece = board.getPiece(move._source);
    auto potenMoves = board.getPiecesPotenMoves(currentColor);
    int beforeTotalCover = static_cast<int>(potenMoves.size());
    int beforeMoveCenterCover = calculateCenterCover(potenMoves);
    board.pieceMove(move._destination, movingPiece);

    // Maximizing player
    if (currentColor == maximizing) {
        if (destPiece) move._score += pieceScore(destPiece->getId()); // capture bonus
        move._score += getMaxThreatScore(currentColor, move._destination, board);
        move._score -= getMinThreatScore(currentColor, move._destination, board);
        if(board.isCheck(colorNot(currentColor)) && board.getPiecesPotenMoves(colorNot(currentColor)).empty()){
            move._score += MATE_SCORE; // Checkmate bonus
        }
        potenMoves.insert(movingPiece->getPotenMoves().begin() , movingPiece->getPotenMoves().end());
        int afterMoveCenterCover = calculateCenterCover(potenMoves);
        if(afterMoveCenterCover - beforeMoveCenterCover > 0){
            move._score += CENTER_COVER_SCORE * (afterMoveCenterCover - beforeMoveCenterCover);
        }
        int afterTotalCover = static_cast<int>(potenMoves.size());
        if(afterTotalCover - beforeTotalCover > 0 ){
            move._score += TOTAL_COVER_SCORE * (afterTotalCover - beforeTotalCover);
        }

    } else {// Minimizing player
        if (destPiece) move._score -= pieceScore(destPiece->getId());// capture bonus
        move._score -= getMaxThreatScore(currentColor, move._destination, board);
        move._score += getMinThreatScore(currentColor, move._destination, board);
        if(board.isCheck(colorNot(currentColor)) && board.getPiecesPotenMoves(colorNot(currentColor)).empty()){
            move._score -= MATE_SCORE; // Checkmate penalty
        }
        // Center control heuristic for minimizing player
        potenMoves.insert(movingPiece->getPotenMoves().begin() , movingPiece->getPotenMoves().end());
        int afterMoveCenterCover = calculateCenterCover(potenMoves);
        if(afterMoveCenterCover - beforeMoveCenterCover > 0){
            move._score -= CENTER_COVER_SCORE * (afterMoveCenterCover - beforeMoveCenterCover);
        }
        int afterTotalCover = static_cast<int>(potenMoves.size());
        if(afterTotalCover - beforeTotalCover > 0 ){
            move._score -= TOTAL_COVER_SCORE * (afterTotalCover - beforeTotalCover);
        }
    }

    // Switch to the opponent's turn
    currentColor = colorNot(currentColor);
    auto legalMoves = board.getAllLegalMoves(currentColor);

    if (legalMoves.empty()) return move._score;// No moves left

    int bestScore = (currentColor == maximizing) ? INT_MIN : INT_MAX;
    // Evaluate all possible moves for the opponent
    for (auto& nextMove : legalMoves) {
        auto destinationPiece = board.getPiece(nextMove._destination);
        if (destinationPiece){
            destinationPiece = destinationPiece->clone();
        }
        auto sourcePiece = board.getPiece(nextMove._source)->clone();
        int score = minimax(depth - 1, nextMove, board, maximizing, currentColor, alpha, beta);
        undoMove(nextMove,board,sourcePiece,destinationPiece);
        if (currentColor == maximizing) {
            bestScore = std::max(bestScore, score);
            alpha = std::max(alpha, bestScore);
        } else {
            bestScore = std::min(bestScore, score);
            beta = std::min(beta, bestScore);
        }

        if (beta <= alpha) break; // pruning
    }
    return move._score + bestScore;
}
/**
* @brief Undoes a move by restoring the board state to its previous configuration.
* @param move The move to be undone.
* @param board The current board state.
* @param sourcePiece The piece that was moved from the source coordinate.
* @param destPiece The piece that was captured (if any).
*/
 void undoMove(Move move , Pieces &board , const std::shared_ptr<Piece> & sourcePiece, const std::shared_ptr<Piece> & destPiece) {
    try{
        board.addPiece(sourcePiece);
        board.removePiece(move._destination);
        if (destPiece) {
            board.addPiece(destPiece);
        }
    }
    catch (NullPiece& e){
        std::cerr << e.what();
    }
}
/**
 * @brief Checks if a given coordinate is within the center of the board.
 * The center of the board is defined by the rows between UP_CENTER_ROW and DOWN_CENTER_ROW,
 * and the columns between LEFT_CENTER_COLL and RIGHT_CENTER_COLL.
 * @param location The coordinate to check (represented as a pair of row and column).
 * @return True if the coordinate is within the board's center; otherwise, false.
 */
bool isInBoardCenter(Coordinate location) {
    return (location.first >= UP_CENTER_ROW && location.first <= DOWN_CENTER_ROW && location.second >= LEFT_CENTER_COLL and location.second <=  RIGHT_CENTER_COLL) ;
}
/**
 * @brief Calculates the number of pieces within the center area of the board.
 * This function iterates through a set of coordinates, checking whether each one is in the
 * center of the board (as defined by the `isInBoardCenter` function). It returns the count of
 * pieces within the center.
 * @param set A set of coordinates representing the locations of pieces on the board.
 * @return The number of pieces located in the center of the board.
 */
int calculateCenterCover(const std::set<Coordinate>& set) {
    int result = 0;
    for(auto coord : set){
        if(isInBoardCenter(coord))result++;
    }
    return result;
}
