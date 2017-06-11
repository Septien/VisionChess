#ifndef CHESSBOARD_H_INCLUDED
#define CHESSBOARD_H_INCLUDED

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "auxiliarFunc.h"

using namespace cv;
using namespace std;

/**
** Class for storing the position of the board and its squares.
** contours -> contours of all the squares of the board.
** mc -> center of mass of all squares.
** boardCenter -> Center of the board
** squareWidth -> Avarage width of the squares of the board.
** squareHeight -> Avarage height of the squares of the board.
*/
class chessBoard
{
private:
    vector<Point2i> mc;
    Point2f boardCenter;
    int squareWidth;
    int squareHeight;

    /**
    ** Get the contours of the objects in the 'edges' image.
    ** Stores only the contours of the objects with an area grater than 400 an less than 50000.
    ** edges -> Image of edges.
    */
    void getContours(Mat &, vector<vector <Point> > &);

    /**
    ** Gets the center of mass of all the squares. It gets the center of mass by first getting
    ** a polygon approximation of the squars, then getting the bounding rectangle, and then, using
    ** the top-left coordinates and width and height of the rectangle, the center is calculated.
    */
    void getCenterOfMass(vector<vector <Point> > &);

public:
    chessBoard();
    ~chessBoard();

    /**
    ** It recieves an image of the chess board with no pieces in it.
    ** Calculates the center of mass of the board.
    ** Finds all the squares within the board and calculates their center of mass.
    ** filename -> path to the image (relative to the project or absolute).
    */
    void loadBoardFromImage(char *);

    /**
    ** Recieve an image with the of to be used.
    ** Calculates the center of mass of the new board and calculate the
    ** displacement with respect of the current board.
    ** Update coordinates so both boards are concurrent.
    ** chess -> grayscale image with the current board.
    */
    void setGameBoard(Mat &);

    /**
    ** Return the ith center of mass.
    */
    Point2i getIthMC(int);
};

#endif // CHESSBOARD_H_INCLUDED
