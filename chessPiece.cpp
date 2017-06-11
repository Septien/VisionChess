#include "chessPiece.h"

chessPiece::chessPiece()
{

}

chessPiece::~chessPiece()
{

}

void chessPiece::setType(pieceType ntype)
{
    type = ntype;
}

void chessPiece::setColor(Color ncolor)
{
    color = ncolor;
}

void chessPiece::setPosition(Point2i nposition)
{
    position = nposition;
}

void chessPiece::setAlive(bool nAlive)
{
    alive = nAlive;
}

pieceType chessPiece::getType()
{
    return type;
}

Color chessPiece::getColor()
{
    return color;
}

Point2i chessPiece::getPosition()
{
    return position;
}

bool chessPiece::isAlive()
{
    return alive;
}
