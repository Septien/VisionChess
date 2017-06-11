#ifndef CHESSPIECE_H_INCLUDED
#define CHESSPIECE_H_INCLUDED

#include <opencv2/opencv.hpp>

using namespace cv;

/**
** Defines the types of pieces in a chess game
*/
enum pieceType {KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN};

/**
** Color of the piece
*/
enum Color {WHITE, BLACK};

/**
** Stores relevant information of the piece.
** type -> type of the piece.
** color -> black or white
*/
class chessPiece
{
private:
    pieceType type;
    Color color;
    Point2i position;
    bool alive;

public:
    chessPiece();
    ~chessPiece();

    void setType(pieceType);
    void setColor(Color);
    void setPosition(Point2i);
    void setAlive(bool);

    pieceType getType();
    Color getColor();
    Point2i getPosition();
    bool isAlive();
};

#endif // CHESSPIECE_H_INCLUDED
