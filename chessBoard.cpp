#include "chessBoard.h"

/**
** Helper functions.
*/
bool pointCompareY(Point, Point);
bool pointCompareX(Point, Point);

chessBoard::chessBoard()
{
    // Previously found
    squareWidth = 30;
    squareHeight = 35;
}

chessBoard::~chessBoard()
{

}

/**
** Get the contours of the objects in the 'edges' image.
** Stores only the contours of the objects with an area grater than 400 an less than 50000.
** edges -> Image of edges.
*/
void chessBoard::getContours(Mat &edges)
{
    // Find all contours within the image
    vector<vector <Point> > allContours;
    vector<Vec4i> heriarchy;
    findContours(edges, allContours, heriarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_TC89_KCOS, Point(0, 0));

    size_t i;

    // Maximum area of squares
    int maxArea = 400;
    int boardArea = 50000;
    vector<Point> center;
    // Get the contours of only an area greater than 400 pixels2.
    // Squares and board
    for (i = 0; i < allContours.size(); i++)
    {
        // Get the contours with area greater than 400
        if (contourArea(allContours[i]) > maxArea)
        {
            // Get the center of mass of the board
            if (contourArea(allContours[i]) > boardArea)
                center = allContours[i];
            // All the other squares
            else
                contours.push_back(allContours[i]);
        }
    }

    // Get center of board
    vector<Point> contour_poly;
    Rect boundingR;
    approxPolyDP(Mat(center), contour_poly, 3, false);
    boundingR = boundingRect(Mat(contour_poly));
    boardCenter = Point2f( boundingR.x + (boundingR.width/2), boundingR.y + (boundingR.height/2) );
}

/**
** Gets the center of mass of all the squares. It gets the center of mass by first getting
** a polygon approximation of the squars, then getting the bounding rectangle, and then, using
** the top-left coordinates and width and height of the rectangle, the center is calculated.
*/
void chessBoard::getCenterOfMass()
{
    size_t i;
    // Points for the approximation polygon.
    vector< vector<Point> > contours_poly(contours.size());
    // Bounding Rectangle.
    vector<Rect> boundingR(contours.size());
    mc = vector<Point2i>(contours.size());
    for (i = 0; i < contours.size(); i++)
    {
        // Get the approximation.
        approxPolyDP(Mat(contours[i]), contours_poly[i], 3, false);
        // Calculate the bounding rectangle.
        boundingR[i] = boundingRect(Mat(contours_poly[i]));
        // Adjust width and height to the nearest 30, 35 value.
        boundingR[i].width = (boundingR[i].width <= 30 ? boundingR[i].width : boundingR[i].width - (boundingR[i].width%31));
        boundingR[i].height = (boundingR[i].height <= 35 ? boundingR[i].height : boundingR[i].height - (boundingR[i].height%36));
        Point c(boundingR[i].x+(boundingR[i].width/2), boundingR[i].y+(boundingR[i].height/2));
        mc[i] = c;
        mc[i].y += 2;
        // Adjust y coordinate to the nearest multiple of ten.
        mc[i].y = ((mc[i].y % 10) == 0 ? mc[i].y : mc[i].y + (10 - (mc[i].y % 10)));
    }

    // Sort center of mass from left to right and top to bottom.
    stable_sort(mc.begin(), mc.end(), pointCompareX);
    stable_sort(mc.begin(), mc.end(), pointCompareY);
}

/**
** It recieves an image of the chess board with no pieces in it.
** Calculates the center of mass of the board.
** Finds all the squares within the board and calculates their center of mass.
** filename -> path to the image (relative to the project or absolute).
*/
void chessBoard::loadBoardFromImage(char *filename)
{
    Mat board = imread(filename, IMREAD_GRAYSCALE);

    // Apply smoothing
    // Size of the kernel for the gaussian blur
    int kernelX, kernelY;
    kernelX = 3;
    kernelY = 3;
    Size ksize(kernelX, kernelY);
    GaussianBlur(board, board, ksize, 1.5, 1.5);

    // Find edges
    Mat edges;
    Canny(board, edges, 10, 30, 3, true);

    // Apply dilation to close open edges
    Mat structElement = getStructuringElement(MORPH_RECT, Size(8, 9));
    dilate(edges, edges, structElement);

    getContours(edges);

    getCenterOfMass();
}

/**
** Recieve an image with the of to be used.
** Calculates the center of mass of the new board and calculate the
** displacement with respect of the current board.
** Update coordinates so both boards are concurrent.
** chess -> grayscale image with the current board.
*/
void chessBoard::setGameBoard(Mat &chess)
{
    Mat edges;
    int kernelX, kernelY;
    kernelX = 3;
    kernelY = 3;
    Size ksize(kernelX, kernelY);
    GaussianBlur(edges, edges, ksize, 1.5, 1.5);
    Canny(chess, edges, 15, 45, 3, true);

    // Find all contours within the image
    vector<vector <Point> > allContours;
    vector<Vec4i> heriarchy;
    findContours(edges, allContours, heriarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_TC89_KCOS, Point(0, 0));

    int i;

    int minBoardArea = 50000;
    vector<Point> centerC;
    // Get the contours of only an area greater than 400 pixels2.
    // Squares and board
    for (i = 0; i < allContours.size(); i++)
    {
        // Get the center of mass of the board
        if (contourArea(allContours[i]) > minBoardArea)
            centerC = allContours[i];
    }

    // Get center of board
    vector<Point> contour_poly;
    Rect boundingR;
    approxPolyDP(Mat(centerC), contour_poly, 3, false);
    boundingR = boundingRect(Mat(contour_poly));
    Point2f center = Point2f( boundingR.x + (boundingR.width/2), boundingR.y + (boundingR.height/2) );

    // Get board displacement
    Point2i displacement = boardCenter - center;

    // Displace center of mass
    for (i = 0; i < mc.size(); i++)
        mc[i] += displacement;
}

Point2i chessBoard::getIthMC(int i)
{
    return mc.at(i);
}

bool pointCompareX(Point a, Point b)
{
    return (a.x < b.x);
}

bool pointCompareY(Point a, Point b)
{
    return a.y < b.y;
}
