#ifndef CHESSBOARD_H_INCLUDED
#define CHESSBOARD_H_INCLUDED

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/**
** Class for storing the position of the board and the squares.
*/
class chessBoard
{
private:
    vector<vector <Point> > contours;
    vector<Point2i> mc;
    Point2f boardCenter;
    int squareWidth;
    int squareHeight;

    void getContours(Mat &);
    void getCenterOfMass();

public:
    chessBoard();
    ~chessBoard();
    void loadBoardFromImage(char *);
    void setGameBoard(Mat &);
    Point2i getIthMC(int);
};

#endif // CHESSBOARD_H_INCLUDED
