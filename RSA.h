#include <iostream>
#include <sstream>
#include "BigInt.h"
#include <stdlib.h> 
#include <time.h> 


void int2str(const int& int_temp, string& string_temp);
//יצירת מספר ראשוני
CBigInt newPrime();
// פונקציה היוצרת מספר ראשוני הקטן מערך נתון (fyn)
CBigInt newPrime_e(CBigInt fyn);

//פונקציה המבצעת חישוב חזקה מודולרית ע"י כפל מודולרי חוזר
CBigInt Power(const CBigInt& x, const CBigInt& n,const CBigInt& p);

//מיישמת את אלגוריתם אוקלידס המורחב למציאת מחלק משותף מקסימלי (GCD) 
//ושני מקדמים כך ש ax + by = gcd(a, b).
CBigInt ExGcd(CBigInt a, CBigInt b, CBigInt& x, CBigInt& y);

//חישוב המפתח הפרטי
CBigInt inverse(const CBigInt& fyn, const CBigInt& e);
// פונקציה ליצירת מפתחות
void generateKeys(CBigInt& n, CBigInt& e, CBigInt& d);

// פונקציה להצפנה
void EncRSA(string message, CBigInt e, CBigInt n);

// פונקציה לפענוח
void DecRSA(string cipher, CBigInt d, CBigInt n);
