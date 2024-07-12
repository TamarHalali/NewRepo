#include "BigInt.h"
#include <cmath>  
#include <algorithm>  
#include <cassert>  


CBigInt::~CBigInt() {}

CBigInt::CBigInt() : values(""), flag(true) {}

CBigInt::CBigInt(const int i) {
    values.clear();
    flag = i >= 0;
    int v = abs(i);
    while (v) {
        values.push_back(char('0' + (v % 10)));
        v /= 10;
    }
    reverse(values.begin(), values.end());
    if (values.empty()) {
        values.push_back('0');
        flag = true;
    }
}

CBigInt::CBigInt(const string& strValues) {
    setValue(strValues);
}

CBigInt::CBigInt(const CBigInt& bigInt) : values(bigInt.values), flag(bigInt.flag) {}


const CBigInt CBigInt::absolute() const {
    CBigInt ret(*this);
    ret.flag = true;
    return ret;
}

int CBigInt::compareBitInt(const CBigInt& rhs) const {
    if (flag && !rhs.flag) return 1;
    if (!flag && rhs.flag) return -1;

    int ret = values.length() > rhs.values.length() ? 1 : values.length() < rhs.values.length() ? -1 : values.compare(rhs.values);

    return flag ? ret : -ret;
}

void CBigInt::setValue(const string& strValues) {
    values.clear();
    string tmpStr(strValues.begin() + strValues.find_first_not_of(' '), strValues.end());
    if (tmpStr.empty()) {
        values.push_back('0');
        flag = true;
        return;
    }

    flag = tmpStr.at(0) != '-';
    int i = tmpStr.find_first_of("0123456789");
    int j = tmpStr.find_last_of("0123456789");

    values = tmpStr.substr(i, j - i + 1);
}

CBigInt& CBigInt::operator=(const CBigInt& rhs) {
    values = rhs.values;
    flag = rhs.flag;
    return *this;
}

ostream& operator<<(ostream& ou, const CBigInt& bigInt) {
    if (!bigInt.flag)
        ou << '-';
    ou << bigInt.values;
    return ou;
}

istream& operator>>(istream& in, CBigInt& bigInt) {
    string str;
    in >> str;
    bigInt.setValue(str);
    return in;
}

const CBigInt operator+(const CBigInt& lhs, const CBigInt& rhs) {
    CBigInt ret;
    if (lhs.flag == rhs.flag) {
        string lvalues(lhs.values), rvalues(rhs.values);
        reverse(lvalues.begin(), lvalues.end());
        reverse(rvalues.begin(), rvalues.end());

        int i = 0;
        for (; i < lvalues.length() && i < rvalues.length(); ++i)
            ret.values.push_back(lvalues.at(i) + rvalues.at(i) - '0');

        if (i < lvalues.length())
            for (; i < lvalues.length(); ++i)
                ret.values.push_back(lvalues.at(i));
        else
            for (; i < rvalues.length(); ++i)
                ret.values.push_back(rvalues.at(i));

        int carry = 0;
        for (int i = 0; i < ret.values.length(); ++i) {
            int newValue = ret.values.at(i) - '0' + carry;
            carry = newValue / 10;
            ret.values.at(i) = newValue - carry * 10 + '0';
        }
        if (carry)
            ret.values.push_back(carry + '0');

        ret.flag = lhs.flag;
    }
    else {
        CBigInt absL = lhs.absolute();
        CBigInt absR = rhs.absolute();
        int compFlag = absL.compareBitInt(absR);
        if (compFlag == 0) {
            ret.setValue("0");
            ret.flag = true;
            return ret;
        }
        else {
            if (compFlag == -1) {
                CBigInt tmp(absL);
                absL = absR;
                absR = tmp;
            }

            reverse(absL.values.begin(), absL.values.end());
            reverse(absR.values.begin(), absR.values.end());

            int i = 0;
            for (; i < absL.values.length() && i < absR.values.length(); ++i)
                ret.values.push_back(absL.values.at(i) - absR.values.at(i) + '0');

            if (i < absL.values.length())
                for (; i < absL.values.length(); ++i)
                    ret.values.push_back(absL.values.at(i));

            int carry = 0;
            for (i = 0; i < ret.values.length(); ++i) {
                int newValue = ret.values.at(i) - carry - '0';
                carry = newValue < 0 ? 1 : 0;
                ret.values.at(i) = newValue + carry * 10 + '0';
            }

            ret.flag = compFlag == 1 ? lhs.flag : rhs.flag;
        }
    }

    reverse(ret.values.begin(), ret.values.end());
    int i = ret.values.find_first_not_of(" 0");
    if (i == string::npos) {
        ret.setValue("0");
        ret.flag = true;
        return ret;
    }
    ret.values = string(ret.values.begin() + ret.values.find_first_not_of(" 0"), ret.values.end());
    return ret;
}

const CBigInt operator-(const CBigInt& lhs, const CBigInt& rhs) {
    CBigInt tmpRhs(rhs);
    tmpRhs.flag = !tmpRhs.flag;
    return lhs + tmpRhs;
}

const CBigInt operator*(const CBigInt& lhs, const CBigInt& rhs) {
    CBigInt ret;
    int flag1 = lhs.compareBitInt(CBigInt(0));
    int flag2 = rhs.compareBitInt(CBigInt(0));
    if (flag1 == 0 || flag2 == 0) {
        ret.setValue("0");
        ret.flag = true;
        return ret;
    }
    ret.flag = lhs.flag == rhs.flag;

    string lvalues(lhs.values), rvalues(rhs.values);
    reverse(lvalues.begin(), lvalues.end());
    reverse(rvalues.begin(), rvalues.end());
    ret.values.resize(lvalues.size() + rvalues.size(), '0');

    for (int i = 0; i < lvalues.size(); ++i)
        for (int j = 0; j < rvalues.size(); ++j) {
            int newValue = ret.values[i + j] + (lvalues[i] - '0') * (rvalues[j] - '0') - '0';
            int carry = newValue / 10;
            ret.values[i + j] = newValue % 10 + '0';

            for (int k = i + j + 1; carry != 0 && k < ret.values.size(); ++k) {
                ret.values[k - 1] = newValue % 10 + '0';
                newValue = ret.values[k] + carry - '0';
                ret.values[k] = newValue % 10 + '0';
                carry = newValue / 10;
            }
        }

    reverse(ret.values.begin(), ret.values.end());
    ret.values = string(ret.values.begin() + ret.values.find_first_not_of(" 0"), ret.values.end());

    return ret;
}

const CBigInt operator/(const CBigInt& lhs, const CBigInt& rhs) {
    CBigInt ret;
    assert(rhs.compareBitInt(CBigInt(0)) != 0);
    ret.setValue("0");

    CBigInt absL(lhs.absolute());
    CBigInt absR(rhs.absolute());

    int comFlag = absL.compareBitInt(absR);
    if (comFlag < 0)
        return ret;
    if (comFlag == 0) {
        ret.setValue("1");
        ret.flag = lhs.flag == rhs.flag;
        return ret;
    }
    int movCount = absL.values.size() - absR.values.size();
    const CBigInt tenBigInt(10);

    do {
        CBigInt tmp(absR);
        for (int i = 0; i < movCount; ++i)
            tmp = tmp * tenBigInt;
        int addNum = 0;
        while (absL.compareBitInt(tmp) >= 0) {
            absL = absL - tmp;
            addNum++;
        }

        ret = ret * tenBigInt + CBigInt(addNum);
        movCount--;

    } while (movCount >= 0);

    ret.flag = lhs.flag == rhs.flag;
    return ret;
}

const CBigInt operator%(const CBigInt& lhs, const CBigInt& rhs) {
    CBigInt divTmp = lhs / rhs;
    return lhs - rhs * divTmp;
}

const bool operator<(const CBigInt& lhs, const CBigInt& rhs) {
    if (!lhs.flag)
        return true;
    if (lhs.values.length() < rhs.values.length())
        return true;
    int m_values = lhs.values.compare(rhs.values);
    return m_values < 0;
}

const bool operator==(const CBigInt& lhs, const string& rhs) {
    return lhs.values.compare(rhs) == 0;
}
