#include <iostream>
#include <sstream>
#include "BigInt.h"
#include <stdlib.h> 
#include <time.h> 
using namespace std;

#define size 1

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

		for (int i = 0; i < size; i++) {
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
CBigInt newPrime_e(CBigInt fyn)
{

	int aa; string myPrimestr = "";
	srand((unsigned)time(NULL));
	bool flag = true, flag2 = true;
	while (flag) {
		for (int i = 0; i < size; i++) {
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

//פונקציה המבצעת חישוב חזקה מודולרית ע"י כפל מודולרי חוזר
CBigInt Power(const CBigInt& x, const CBigInt& n,
	const CBigInt& p)
{
	if (n == "0")
		return 1;

	CBigInt tmp = Power((x * x) % p, n / CBigInt(2), p);

	if (n % CBigInt(2) == "0")
		;
	else
		tmp = (tmp * x) % p;

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
	cout << "The p is " << p << ". The q is " << q << ". The e is " << e << ". The n is " << n << ". The d is " << d << ". (E is public key. D is private key.)\n";
}

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
	generateKeys(n, e, d);
	string c;
	cout << "Enter number to decrypt: ";
	cin >> c;
	CBigInt c_big(c);
	CBigInt m = Power(c_big, d, n);
	cout << "Decrypted: " << m << endl;
}

//int main()
//{
//
//	int choice;
//	cout << "1. Encrypt\n2. Decrypt\nChoose an option: ";
//	cin >> choice;
//	if (choice == 1) {
//		EncRSA();
//	}
//	else if (choice == 2) {
//		DecRSA();
//	}
//	else {
//		cout << "Invalid choice.\n";
//	}
//	return 0;
//}

int main()
{
	cout << "start\n";
	CBigInt p = newPrime();
	CBigInt q = newPrime();
	CBigInt p1 = p - CBigInt(1);
	CBigInt q1 = q - CBigInt(1);
	CBigInt fyn = p1 * q1;
	CBigInt n = p * q;
	CBigInt e = newPrime_e(fyn);
	CBigInt d = inverse(fyn, e);
	cout << " The p is " << p << ".The q is " << q << ".The e is " << e << ".The n is " << n << ".The d is " << d << ".(E is public key.D is primary key.)\n";
	string m;
	cout << "enter number: " << endl;
	cin >> m;
	CBigInt m_big1(m);
	CBigInt C = Power(m_big1, e, n);
	cout << "C " << C << endl;
	m_big1 = Power(C, d, n);
	cout << "m_big1" << m_big1 << endl << endl << endl;
	cout << "bla: " << endl;
	cin >> m;
	CBigInt m_big2(m);
	C = Power(m_big2, d, n);
	cout << "C: " << C << endl;
	m_big2 = Power(C, e, n);
	cout << "m_big2 " << m_big2 << endl << endl << endl;
	return 0;
}