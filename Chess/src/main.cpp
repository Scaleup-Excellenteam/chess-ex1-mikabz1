#include "../include/Chess.h"
#include "../include/Pieces.h"
#include "../include/Common.h"
#include "../include/Move.h"
#include "../include/Constants.h"
#include "../include/PriorityQueue.h"
#include "../include/PriorityAlgo.h"
#include <chrono>

int main()
{
    PriorityQueue<Move> priorityQueue;
//	string strBoard = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
	string strBoard = "##########K###############################R#####q#######r#######";
//    string strBoard = "##########K###############################R#####q#######r#######";
//    string strBoard = "###############################p######################P#########";

    Chess a(strBoard);
	int codeResponse = 0;
    Pieces mainBoard(strBoard);
    COLOR turn = WHITE;

    mainBoard.updatePotenMoves(turn);
    priorityQueue = mainAlgo(RECURSION_DEPTH , turn,mainBoard);
    priorityQueue.print();

    string res = a.getInput();
	while (res != "exit")
	{
        // Convert the input string into source and target coordinates
        std::pair<Coordinate ,Coordinate> move = stringToCoordinate(res);
        Coordinate source = flipChessCoord(move.first);
        Coordinate target = flipChessCoord(move.second);

        // Retrieve the pieces at the source and target positions
        const std::shared_ptr<Piece>& sourcePiece = mainBoard.getPiece(source);
        const std::shared_ptr<Piece>& targetPiece = mainBoard.getPiece(target);

        // Check if the move is valid, handle errors accordingly
        if(sourcePiece == nullptr)codeResponse = ERROR_NO_PIECE_AT_SOURCE;
        else if(sourcePiece->getColor() != turn)codeResponse = ERROR_WRONG_COLOR_AT_SOURCE;
        else if(targetPiece != nullptr && targetPiece->getColor() == turn)codeResponse = ERROR_TARGET_HAS_FRIENDLY;
        else if(!sourcePiece->isValidMove(target , mainBoard))codeResponse = ERROR_ILLEGAL_MOVE;
        else if(sourcePiece->willBeInCheck(target , mainBoard))codeResponse = ERROR_MOVE_CAUSES_CHECK;
        else {
            mainBoard.makeMove(target , sourcePiece);
            turn = colorNot(turn);
            mainBoard.updatePotenMoves(turn);
            mainBoard.isCheck(turn) ? codeResponse = STATUS_CHECK : codeResponse = STATUS_OK;
        }
        a.setCodeResponse(codeResponse);
        priorityQueue = mainAlgo(RECURSION_DEPTH , turn,mainBoard);
        priorityQueue.print();
		res = a.getInput();
	}
	cout << endl << "Exiting " << endl;
	return 0;
}










