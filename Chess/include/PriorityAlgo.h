#pragma once
#include "Common.h"
#include "Pieces.h"
#include "PriorityQueue.h"



/// @brief Returns the base score assigned to a given piece type.
/// @param id The ID representing the piece type.
/// @return The score value associated with the piece.
int pieceScore(ID);
/// @brief Computes the minimum threat score to a specific coordinate for the given color.
/// @param color The color of the player being evaluated.
/// @param coord The coordinate to check for threats.
/// @param pieces The current board state.
/// @return The lowest threat score from opponent pieces.
int getMinThreatScore(COLOR ,Coordinate ,Pieces&);
/// @brief Computes the maximum threat score a piece can inflict on a coordinate for the given color.
/// @param color The color of the player being evaluated.
/// @param coord The coordinate to check for threats.
/// @param pieces The current board state.
/// @return The highest threat score to the coordinate.
int getMaxThreatScore(COLOR ,Coordinate ,Pieces&);
/// @brief Executes the main move selection algorithm with prioritization.
/// @param depth The maximum recursion depth for evaluation.
/// @param playerColor The color of the player making the move.
/// @param pieces The current board state.
/// @return A priority queue of evaluated moves sorted by desirability.
PriorityQueue<Move> mainAlgo(int,COLOR,Pieces&);
/// @brief Minimax algorithm with alpha-beta pruning to evaluate moves.
/// @param depth The remaining search depth.
/// @param move The current move being evaluated.
/// @param board The current board state.
/// @param maximizing The color of the maximizing player.
/// @param currentColor The color whose turn it is.
/// @param alpha The best value the maximizer can guarantee.
/// @param beta The best value the minimizer can guarantee.
/// @return The evaluation score for the current move.
int minimax(int depth, Move move, Pieces& board, COLOR maximizing, COLOR currentColor, int alpha, int beta);
/// @brief Reverts a move on the board, restoring the previous state.
/// @param move The move to undo.
/// @param board The current board state.
/// @param movedPiece The piece that was moved.
/// @param capturedPiece The piece that was captured (if any).
void undoMove(Move move, Pieces& board, const std::shared_ptr<Piece>&,const std::shared_ptr<Piece>&);
/// @brief Checks whether a coordinate lies within the central area of the board.
/// @param coord The coordinate to evaluate.
/// @return True if the coordinate is in the center, false otherwise.
bool isInBoardCenter(Coordinate);
/// @brief Calculates the central control score based on the set of controlled coordinates.
/// @param coverage A set of coordinates under control by a player.
/// @return The score based on how many of those coordinates are in the center.
int calculateCenterCover(const std::set<Coordinate>&);