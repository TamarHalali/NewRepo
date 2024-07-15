#include <iostream>
#include <sstream>
#include "BigInt.h"
#include <stdlib.h> 
#include <time.h> 
using namespace std;

#define SIZE 1

void int2str(const int& int_temp, string& string_temp)
{
	stringstream stream;
	stream << int_temp;
	string_temp = stream.str();   //stream>>string_temp  
}
//יצירת מספר ראשוני
CBigInt newPrime()
{
	int aa; string myPrimestr = "";
	srand((unsigned)time(NULL));
	bool flag = true, flag2 = true;
	while (flag) {

		for (int i = 0; i < SIZE; i++) {
			aa = rand();
			int2str(aa, myPrimestr);
		}
		CBigInt myPrime(myPrimestr);
		flag2 = true;
		CBigInt ii("2");
		if (myPrime % ii == "0") {
			continue;
		}
		ii = ii + 1;
		for (; ii < myPrime; ii = ii + 2)
		{
			if (myPrime % ii == "0") {
				flag2 = false;
				break;
			}
		}
		if (flag2)
			return myPrime;
	}
	//  cout << endl; 
	return 0;
}
// פונקציה היוצרת מספר ראשוני הקטן מערך נתון (fyn)
//e
CBigInt newPrime_e(CBigInt fyn)
{

	int aa; string myPrimestr = "";
	srand((unsigned)time(NULL));
	bool flag = true, flag2 = true;
	while (flag) {
		for (int i = 0; i < SIZE; i++) {
			aa = rand();
			int2str(aa, myPrimestr);
		}
		CBigInt myPrime(myPrimestr);
		if (fyn < myPrime)
			continue;
		flag2 = true;
		CBigInt ii("2");
		if (myPrime % ii == "0") {
			continue;
		}
		ii = ii + 1;
		for (; ii < myPrime; ii = ii + 2)
		{
			if (myPrime % ii == "0") {
				flag2 = false;
				break;
			}
		}
		if (flag2)
			return myPrime;
	}
	//  cout << endl; 
	return 0;
}
//להחליף את השמות בהתאמה
//פונקציה המבצעת חישוב חזקה מודולרית ע"י כפל מודולרי חוזר

CBigInt Power(const CBigInt& mc, const CBigInt& n,
	const CBigInt& p)
{
	if (n == "0")
		return 1;

	CBigInt tmp = Power((mc * mc) % p, n / CBigInt(2), p);

	if (n % CBigInt(2) == "0")
		;
	else
		tmp = (tmp * mc) % p;

	return tmp;
}

//מיישמת את אלגוריתם אוקלידס המורחב למציאת מחלק משותף מקסימלי (GCD) 
//ושני מקדמים כך ש ax + by = gcd(a, b).
CBigInt ExGcd(CBigInt a, CBigInt b, CBigInt& x, CBigInt& y)
{
	if (b == "0")
	{
		x = 1;
		y = 0;
		return a;
	}
	CBigInt r = ExGcd(b, a % b, x, y);
	CBigInt t = x;
	x = y;
	y = t - a / b * y;
	return r;
}

//חישוב המפתח הפרטי
CBigInt inverse(const CBigInt& fyn, const CBigInt& e)
{
	//int fyn = ( 1 - p ) * ( 1 - q );
	CBigInt x, y;

	ExGcd(fyn, e, x, y);
	if (y < CBigInt("0"))
		y = y + fyn;
	return y;
}

// פונקציה ליצירת מפתחות
void generateKeys(CBigInt& n, CBigInt& e, CBigInt& d)
{
	cout << "Generating keys...\n";
	CBigInt p = newPrime();
	CBigInt q = newPrime();
	CBigInt p1 = p - CBigInt(1);
	CBigInt q1 = q - CBigInt(1);
	CBigInt fyn = p1 * q1;
	n = p * q;
	e = newPrime_e(fyn);
	d = inverse(fyn, e);
	//מה הפרטי ומה הציבורי
	cout << "The p is " << p << ". The q is " << q << ". The e is " << e << ". The n is " << n << ". The d is " << d << ". (E is public key. D is private key.)\n";
}
//שתקבל שם של קובץ
// פונקציה להצפנה
void EncRSA()
{
	CBigInt n, e, d;
	generateKeys(n, e, d);
	string m;
	cout << "Enter number to encrypt: ";
	cin >> m;
	CBigInt m_big(m);
	CBigInt C = Power(m_big, e, n);
	cout << "Encrypted: " << C << endl;
}

// פונקציה לפענוח
void DecRSA()
{
	CBigInt n, e, d;
	//generateKeys(n, e, d);
	string c;
	cout << "Enter number to decrypt: ";
	cin >> c;
	CBigInt c_big(c);
	//d=private
	CBigInt m = Power(c_big, d, n);
	cout << "Decrypted: " << m << endl;
}

//
//int main()
//{
//	cout << "start\n";
//	CBigInt p = newPrime();
//	CBigInt q = newPrime();
//	CBigInt p1 = p - CBigInt(1);
//	CBigInt q1 = q - CBigInt(1);
//	CBigInt fyn = p1 * q1;
//	CBigInt n = p * q;
//	CBigInt e = newPrime_e(fyn);
//	CBigInt d = inverse(fyn, e);
//	cout << " The p is " << p << ".The q is " << q << ".The e is " << e << ".The n is " << n << ".The d is " << d << ".(E is public key.D is primary key.)\n";
//	string m;
//	cout << "enter number: " << endl;
//	cin >> m;
//	CBigInt m_big1(m);
//	CBigInt C = Power(m_big1, e, n);
//	cout << "C " << C << endl;
//	m_big1 = Power(C, d, n);
//	cout << "m_big1" << m_big1 << endl << endl << endl;
//	cout << "bla: " << endl;
//	cin >> m;
//	CBigInt m_big2(m);
//	C = Power(m_big2, d, n);
//	cout << "C: " << C << endl;
//	m_big2 = Power(C, e, n);
//	cout << "m_big2 " << m_big2 << endl << endl << endl;
//	return 0;
//}
//-----------------------------------------------------------

//
//int main() {
//    int choice;
//    cout << "1. Encrypt\n2. Decrypt\nChoose an option: ";
//    cin >> choice;
//    if (choice == 1) {
//        EncRSA();
//    }
//    else if (choice == 2) {
//        DecRSA();
//    }
//    else {
//        cout << "Invalid choice" << endl;
//    }
//    return 0;
//}
//------------------------------------
//#include <iostream>
//#include <sstream>
//#include "BigInt.h"
//#include <stdlib.h> 
//#include <time.h> 
//#include <string>
//
//using namespace std;
//
//#define SIZE 10
//
//void int2str(const int& int_temp, string& string_temp) {
//    stringstream stream;
//    stream << int_temp;
//    string_temp = stream.str();
//}
//
//CBigInt newPrime() {
//    string myPrimestr = "";
//    srand((unsigned)time(NULL));
//    bool flag = true, flag2 = true;
//    while (flag) {
//        for (int i = 0; i < SIZE; i++) {
//            int aa = rand();
//            int2str(aa, myPrimestr);
//        }
//        CBigInt myPrime(myPrimestr);
//        flag2 = true;
//        CBigInt ii("2");
//        if (myPrime % ii == "0") {
//            continue;
//        }
//        ii = ii + 1;
//        for (; ii < myPrime; ii = ii + 2) {
//            if (myPrime % ii == "0") {
//                flag2 = false;
//                break;
//            }
//        }
//        if (flag2)
//            return myPrime;
//    }
//    return 0;
//}
//
//CBigInt newPrime_e(CBigInt fyn) {
//    string myPrimestr = "";
//    srand((unsigned)time(NULL));
//    bool flag = true, flag2 = true;
//    while (flag) {
//        for (int i = 0; i < SIZE; i++) {
//            int aa = rand();
//            int2str(aa, myPrimestr);
//        }
//        CBigInt myPrime(myPrimestr);
//        if (fyn < myPrime)
//            continue;
//        flag2 = true;
//        CBigInt ii("2");
//        if (myPrime % ii == "0") {
//            continue;
//        }
//        ii = ii + 1;
//        for (; ii < myPrime; ii = ii + 2) {
//            if (myPrime % ii == "0") {
//                flag2 = false;
//                break;
//            }
//        }
//        if (flag2)
//            return myPrime;
//    }
//    return 0;
//}
//
//CBigInt Power(const CBigInt& x, const CBigInt& n, const CBigInt& p) {
//    if (n == "0")
//        return 1;
//
//    CBigInt tmp = Power((x * x) % p, n / CBigInt(2), p);
//
//    if (n % CBigInt(2) != "0")
//        tmp = (tmp * x) % p;
//
//    return tmp;
//}
//
//CBigInt ExGcd(CBigInt a, CBigInt b, CBigInt& x, CBigInt& y) {
//    if (b == "0") {
//        x = 1;
//        y = 0;
//        return a;
//    }
//    CBigInt r = ExGcd(b, a % b, x, y);
//    CBigInt t = x;
//    x = y;
//    y = t - a / b * y;
//    return r;
//}
//
//CBigInt inverse(const CBigInt& fyn, const CBigInt& e) {
//    CBigInt x, y;
//    ExGcd(fyn, e, x, y);
//    if (y < CBigInt("0"))
//        y = y + fyn;
//    return y;
//}
//
//void generateKeys(CBigInt& n, CBigInt& e, CBigInt& d) {
//    cout << "Generating keys...\n";
//    CBigInt p = newPrime();
//    CBigInt q = newPrime();
//    CBigInt p1 = p - CBigInt(1);
//    CBigInt q1 = q - CBigInt(1);
//    CBigInt fyn = p1 * q1;
//    n = p * q;
//    e = newPrime_e(fyn);
//    d = inverse(fyn, e);
//    cout << "The p is " << p << ". The q is " << q << ". The e is " << e << ". The n is " << n << ". The d is " << d << ". (E is public key. D is private key.)\n";
//}
//
//CBigInt stringToBigInt(const string& input) {
//    CBigInt result("0");
//    for (char ch : input) {
//        result = result * CBigInt("256") + CBigInt(to_string(static_cast<int>(ch)));
//    }
//    return result;
//}
//
//string bigIntToString(CBigInt input) {
//    string result;
//    while (input > CBigInt("0")) {
//        int ascii = stoi((input % CBigInt("256")).toString());
//        result = static_cast<char>(ascii) + result;
//        input = input / CBigInt("256");
//    }
//    return result;
//}
//
//string encrypt(const string& message, const CBigInt& e, const CBigInt& n) {
//    CBigInt m = stringToBigInt(message);
//    CBigInt c = Power(m, e, n);
//    return c.toString();
//}
//
//string decrypt(const string& cipher, const CBigInt& d, const CBigInt& n) {
//    CBigInt c(cipher);
//    CBigInt m = Power(c, d, n);
//    return bigIntToString(m);
//}
//
//int main() {
//    CBigInt n, e, d;
//    generateKeys(n, e, d);
//
//    string message = "Hello, RSA!";
//    cout << "Original message: " << message << endl;
//
//    string cipher = encrypt(message, e, n);
//    cout << "Encrypted message: " << cipher << endl;
//
//    string decryptedMessage = decrypt(cipher, d, n);
//    cout << "Decrypted message: " << decryptedMessage << endl;
//
//    return 0;
//}
