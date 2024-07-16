#include <iostream>
#include <sstream>
#include "BigInt.h"
#include <stdlib.h> 
#include <time.h> 


void int2str(const int& int_temp, string& string_temp);
//����� ���� ������
CBigInt newPrime();
// ������� ������ ���� ������ ���� ���� ���� (fyn)
CBigInt newPrime_e(CBigInt fyn);

//������� ������ ����� ���� �������� �"� ��� ������� ����
CBigInt Power(const CBigInt& x, const CBigInt& n,const CBigInt& p);

//������ �� �������� ������� ������ ������ ���� ����� ������� (GCD) 
//���� ������ �� � ax + by = gcd(a, b).
CBigInt ExGcd(CBigInt a, CBigInt b, CBigInt& x, CBigInt& y);

//����� ����� �����
CBigInt inverse(const CBigInt& fyn, const CBigInt& e);
// ������� ������ ������
void generateKeys(CBigInt& n, CBigInt& e, CBigInt& d);

// ������� ������
void EncRSA(string message, CBigInt e, CBigInt n);

// ������� ������
void DecRSA(string cipher, CBigInt d, CBigInt n);
