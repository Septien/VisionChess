#ifndef AUXILIARFUNC_H_INCLUDED
#define AUXILIARFUNC_H_INCLUDED

#include <opencv2/opencv.hpp>

using namespace cv;

/**
** Contains auxiliary functions to be used accros the project.
*/

/**
** Compares y coordinate of the points.
*/
bool pointCompareY(Point, Point);

/**
** Compares x coordinate of the points.
*/
bool pointCompareX(Point, Point);

/**
** Verifies of rectangle b is inside of rectangle a
*/
bool withinRect(Rect a, Rect b);

/**
** Compute euclide distance between two points.
*/
double euclide_distance(Point3d, Point3d);
#endif // AUXILIARFUNC_H_INCLUDED
