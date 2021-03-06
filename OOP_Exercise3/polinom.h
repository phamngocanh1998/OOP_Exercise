#ifndef POLINOM_H
#define POLINOM_H
#include <QString>
#include "number.h"

enum EPrintMode{
    EPrintModeClassic,
    EPrintModeCanonic,
};

class Polinom
{
    EPrintMode printmode;
    number a, b, c;
public:
    Polinom(number, number, number);
    void setPrintMode(EPrintMode);
    number value(number);
    int roots(number[2]);
    friend QString& operator <<(QString&, Polinom&);
};

#endif // POLINOM_H

