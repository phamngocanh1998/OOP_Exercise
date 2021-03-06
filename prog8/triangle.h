#ifndef TTRIANGLE_H
#define TTRIANGLE_H
#define PI (double)3.14159
#include "figure.h"

class TTriangle : public TFigure
{
protected:
    double a, b;
    double angle;
public:
    TTriangle(double, double, double);
    double Area();
    double Perimeter();
};

#endif // TTRIANGLE_H
