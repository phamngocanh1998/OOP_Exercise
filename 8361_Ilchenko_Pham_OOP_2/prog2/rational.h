#ifndef TRATIONAL_H
#define TRATIONAL_H
#include <iostream>

class TRational;

namespace std
{
    TRational abs(TRational);
}

class TRational
{
    int a, b;
    int gcd(int, int);
    void compact();
public:
    TRational();
    TRational(int, int);
    TRational(const int&);
    bool operator ==(const TRational &) const;
    bool operator >=(const TRational &) const;
    bool operator <(const TRational &) const;
    friend TRational operator *(const TRational &, const TRational &);
    TRational operator /(const TRational &) const;
    TRational operator +(const TRational &) const;
    TRational operator -(const TRational &) const;
    TRational operator -() const;
    friend TRational sqrt(TRational);
    friend TRational std::abs(TRational);
    friend std::ostream& operator <<(std::ostream&, TRational);
    friend std::istream& operator >>(std::istream&, TRational&);
};



#endif // TRATIONAL_H
