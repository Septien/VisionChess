#include "auxiliarFunc.h"

bool pointCompareX(Point a, Point b)
{
    return (a.x < b.x);
}

bool pointCompareY(Point a, Point b)
{
    return a.y < b.y;
}

bool withinRect(Rect a, Rect b)
{
    return ((b.x >= a.x) && (b.y >= a.y) && (b.x+b.width <= a.x+a.width) && (b.y+b.height <= a.y+a.height));
}

double euclide_distance(Point3d a, Point3d b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}
