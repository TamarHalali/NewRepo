#ifndef BIGINT_H
#define BIGINT_H

#include <string>
#include <iostream>
using namespace std;

class CBigInt {
public:
    explicit CBigInt();
    ~CBigInt();

    CBigInt(const int i);
    CBigInt(const string& strValues);
    CBigInt(const CBigInt& bigInt);
    bool inline isPositive() { return flag; };
    int compareBitInt(const CBigInt& rhs)const;
    CBigInt& operator = (const CBigInt& rhs);
    friend ostream& operator << (ostream& ou, const CBigInt& bigInt);
    friend istream& operator >> (istream& in, CBigInt& bigInt);
    friend const CBigInt operator + (const CBigInt& lhs, const CBigInt& rhs);
    friend const CBigInt operator - (const CBigInt& lhs, const CBigInt& rhs);
    friend const CBigInt operator * (const CBigInt& lhs, const CBigInt& rhs);
    friend const CBigInt operator / (const CBigInt& lhs, const CBigInt& rhs);
    friend const CBigInt operator % (const CBigInt& lhs, const CBigInt& rhs);
    friend const bool operator < (const CBigInt& lhs, const CBigInt& rhs);
    friend const bool operator == (const CBigInt& lhs, const string& rhs);
    void setValue(const string& strValues);
    const CBigInt absolute()const;

private:

    string values;
    bool flag;
};

#endif // BIGINT_H
