
//#include "RijndaelAlgFst.h"
//#include <time.h>
//#include <fstream>
//#include <iostream>
//#include <random>
//
//using namespace std;
//
//void Enc()
//{
//	//���� ����� ����� 16 ����
//	u8 cipherKey[16]={0x3b ,0x8e, 0x45, 0x76, 0x18, 0xa7, 0x22, 0x11, 0x45, 0xf7, 0xe5, 0xd8, 0xc9, 0xcf, 0x4f, 0x3f};
//	//���� �� ������ ������ (Round Keys) ����� 44 ������ (10 ����� + ���� ������).
//	u32 rk[44];
//	int Nr,i=0,j=0,k=0,p=0;
//	u8 pt[16],ct[16];
//	char ch;
//	int fin1=0,fin2,time=0,max;
//	bool flag = true;
//	//buffer
//	char buffer1[1024],buffer2[1024];
//	//������� ������ �� ������� ������� ������ ������ �� ���� cipherKey
//	Nr=rijndaelKeySetupEnc(rk,cipherKey,128);
//	//
//	ifstream in("message.txt",ios::in||ios::binary);
//	if(!in)
//	{
//		cerr<<"file message cannot be opened/n";
//		exit(1); 
//	}
//
//	ofstream out("cipher.txt",ios::out);
//	if(!out)
//	{
//		cerr<<"file cipher cannot be opened/n";
//		exit(1);
//	}
//	//���� ������ ���� ����� ������.
//	ofstream out2("length.txt",ios::out);
//	if(!out2)
//	{
//		cerr<<"file length cannot be opened/n";
//		exit(1);
//	}
//	
//	in.seekg(0,ios::end);
//	fin1=in.tellg();
//	fin2=fin1;
//	in.seekg(0,ios::beg);
//	out2<<fin1<<" ";
//	
//	////������� ������ ��������� ����� buffer1.
//	//�� 16 ���� ������� ������� rijndaelEncrypt ������� ����� buffer2.
//	//	�� buffer2 ���� ����� ���� ���� ������� 1024 ����.
//	while(flag)
//	{
//		//����� ����� �� ������� ������� �� 1024 ����, �� ����� ������ ������ ����� ����.
//		in.seekg(1024*time,ios::beg);
//		time++;
//		if(fin1>1024)
//		{
//			in.read(buffer1,1024);
//			fin1-=1024;
//			max=1024;
//		}
//		else
//		{
//			in.read(buffer1,fin1);
//			max=fin1;
//			flag=false;
//		}
//		
//		for(k=0;k<max;k++)
//		{
//			pt[i]=buffer1[k];
//			i++;
//			if(i==16)
//			{
//				i=0;
//				rijndaelEncrypt(rk,Nr,pt,ct);
//
//				for(j=0;j<16;j++)
//				{
//					buffer2[p]=ct[j];
//					p++;
//					if(p==1024)
//					{
//						p=0;
//						out.write(buffer2,1024);
//					}
//				}
//			}
//		}
//	}
//	if(i>0&&i<16)
//	{
//		rijndaelEncrypt(rk,Nr,pt,ct);
//		fin2+=(16-i);
//		for(j=0;j<16;j++)
//		{
//			buffer2[p]=ct[j];
//			p++;
//			if(p==1024)
//			{
//				p=0;
//				out.write(buffer2,1024);
//			}
//		}
//	}
//	
//	if(p>0)
//	{
//		out.write(buffer2,p);
//	}
//	
//	out2<<fin2;
//	in.close();
//	out.close();
//	out2.close();
//}
//
//void Dec()
//{
//	//���� �����.
//	u8 cipherKey[16]={0x3b ,0x8e, 0x45, 0x76, 0x18, 0xa7, 0x22, 0x11, 0x45, 0xf7, 0xe5, 0xd8, 0xc9, 0xcf, 0x4f, 0x3f};
//	//���� �� ������ ������.
//	u32 rk[44];
//	int Nr,i=0,j=0,k=0,p=0;
//	u8 pt[16],ct[16];
//	char ch;
//	int fin1,fin2,time=0,max;
//	bool flag = true;
//	char buffer1[1024],buffer2[1024];
//
//	//������� ������ �� ������� ������� ������ ������ �� ���� cipherKey.
//	Nr=rijndaelKeySetupDec(rk,cipherKey,128);
//	
//	ifstream in("cipher.txt",ios::in||ios::binary);
//	if(!in)
//	{
//		cerr<<"file cipher cannot be opened/n";
//		exit(1); 
//	}
//	//length.txt
//	ifstream in2("length.txt",ios::in);
//	if(!in2)
//	{
//		cerr<<"file length cannot be opened/n";
//		exit(1); 
//	}
//	
//	
//	ofstream out("decrypt.txt",ios::out);
//	if(!out)
//	{
//		cerr<<"file decrypt cannot be opened/n";
//		exit(1);
//	}
//	
//	in2>>fin2>>fin1;
//	fin2=fin1-fin2; 
//	in2.close();
//	//������ ������ ������ ������ ������� �� 1024 ����.
//	/*������� ������ ����� buffer1.
//		�� 16 ���� �������� ������� rijndaelDecrypt ������� ����� buffer2.
//		�� buffer2 ���� ����� ���� ���� ������� 1024 ����.*/
//	while(flag)
//	{
//		
//		in.seekg(1024*time,ios::beg);
//		time++;
//		if(fin1>1024)
//		{
//			in.read(buffer1,1024);
//			fin1-=1024;
//			max=1024;
//		}
//		else
//		{
//			in.read(buffer1,fin1);
//			max=fin1;
//			flag=false;
//		}
//		
//		for(k=0;k<max;k++)
//		{
//			pt[i]=buffer1[k];
//			i++;
//			if(i==16)
//			{
//				i=0;
//				rijndaelDecrypt(rk,Nr,pt,ct);
//				
//				for(j=0;j<16;j++)
//				{
//					buffer2[p]=ct[j];
//					p++;
//					if(p==1024)
//					{
//						p=0;
//						out.write(buffer2,1024);
//					}
//				}
//			}
//		}
//	}
//
//	if(p>0)
//	{
//		out.write(buffer2,p-fin2);
//	}
//	in.close();
//	out.close();
//}
////
////void main()
////{
////	clock_t start,finish;
////	double duration1,duration2;
////	int length;
////	
////	start=clock();
////	Enc();
////	finish=clock();
////	duration1=(double)(finish-start);
////	
////	ifstream in("length.txt",ios::in);
////	if(!in)
////	{
////		cerr<<"file length cannot be opened/n";
////		exit(1); 
////	}
////
////	in>>length;
////	in.close();
////	start=clock();
////	Dec();
////	finish=clock();
////	duration2=(double)(finish-start);
////	cout<<"length"<<length<<"length\n";
////	cout<<"duration1"<<duration1<<" ms!"<<endl;
////	cout<<"duration2"<<duration2<<" ms!"<<endl;
////	cout << "bla";
////	char c;
////	//cin.get(c);
////	return;
////}
//
//// ������� ������ ���� �����
//void generateKey(u8 key[16])
//{
//    random_device rd;
//    mt19937 gen(rd());
//    uniform_int_distribution<> dis(0, 255);
//
//    for (int i = 0; i < 16; ++i)
//    {
//        key[i] = static_cast<u8>(dis(gen));
//    }
//}

//--------------------------------------------------------
#include "RijndaelAlgFst.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <iomanip>

using namespace std;

// ������� ������ ���� ������� ������� ����� key.txt
void generateRandomKey(u8* key, int length) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 255);

    ofstream keyFile("key.txt", ios::out | ios::binary);
    if (!keyFile) {
        cerr << "file key.txt cannot be opened\n";
        exit(1);
    }

    for (int i = 0; i < length; ++i) {
        key[i] = dis(gen);
    }

    keyFile.write(reinterpret_cast<char*>(key), length);
    keyFile.close();
}

void Enc() {
    // ����� ���� ������� ����� 16 ���� ������� ����� key.txt
    u8 cipherKey[16];
    generateRandomKey(cipherKey, 16);

    // ���� �� ������ ������ (Round Keys) ����� 44 ������ (10 ����� + ���� ������).
    u32 rk[44];
    int Nr, i = 0, j = 0, k = 0, p = 0;
    u8 pt[16], ct[16];
    char ch;
    int fin1 = 0, fin2, time = 0, max;
    bool flag = true;
    // buffer
    char buffer1[1024], buffer2[1024];
    // ������� ������ �� ������� ������� ������ ������ �� ���� cipherKey
    Nr = rijndaelKeySetupEnc(rk, cipherKey, 128);

    ifstream in("message.txt", ios::in | ios::binary);
    if (!in) {
        cerr << "file message cannot be opened\n";
        exit(1);
    }

    ofstream out("cipher.txt", ios::out);
    if (!out) {
        cerr << "file cipher cannot be opened\n";
        exit(1);
    }
    // ���� ������ ���� ����� ������.
    ofstream out2("length.txt", ios::out);
    if (!out2) {
        cerr << "file length cannot be opened\n";
        exit(1);
    }

    in.seekg(0, ios::end);
    fin1 = in.tellg();
    fin2 = fin1;
    in.seekg(0, ios::beg);
    out2 << fin1 << " ";

    while (flag) {
        in.seekg(1024 * time, ios::beg);
        time++;
        if (fin1 > 1024) {
            in.read(buffer1, 1024);
            fin1 -= 1024;
            max = 1024;
        }
        else {
            in.read(buffer1, fin1);
            max = fin1;
            flag = false;
        }

        for (k = 0; k < max; k++) {
            pt[i] = buffer1[k];
            i++;
            if (i == 16) {
                i = 0;
                rijndaelEncrypt(rk, Nr, pt, ct);

                for (j = 0; j < 16; j++) {
                    buffer2[p] = ct[j];
                    p++;
                    if (p == 1024) {
                        p = 0;
                        out.write(buffer2, 1024);
                    }
                }
            }
        }
    }
    if (i > 0 && i < 16) {
        rijndaelEncrypt(rk, Nr, pt, ct);
        fin2 += (16 - i);
        for (j = 0; j < 16; j++) {
            buffer2[p] = ct[j];
            p++;
            if (p == 1024) {
                p = 0;
                out.write(buffer2, 1024);
            }
        }
    }

    if (p > 0) {
        out.write(buffer2, p);
    }

    out2 << fin2;
    in.close();
    out.close();
    out2.close();
}

void Dec() {
    // ����� ����� ����� key.txt
    u8 cipherKey[16];
    ifstream keyFile("key.txt", ios::in | ios::binary);
    if (!keyFile) {
        cerr << "file key.txt cannot be opened\n";
        exit(1);
    }

    keyFile.read(reinterpret_cast<char*>(cipherKey), 16);
    keyFile.close();

    // ���� �� ������ ������.
    u32 rk[44];
    int Nr, i = 0, j = 0, k = 0, p = 0;
    u8 pt[16], ct[16];
    char ch;
    int fin1, fin2, time = 0, max;
    bool flag = true;
    char buffer1[1024], buffer2[1024];

    // ������� ������ �� ������� ������� ������ ������ �� ���� cipherKey.
    Nr = rijndaelKeySetupDec(rk, cipherKey, 128);

    ifstream in("cipher.txt", ios::in | ios::binary);
    if (!in) {
        cerr << "file cipher cannot be opened\n";
        exit(1);
    }
    // length.txt
    ifstream in2("length.txt", ios::in);
    if (!in2) {
        cerr << "file length cannot be opened\n";
        exit(1);
    }

    ofstream out("decrypt.txt", ios::out);
    if (!out) {
        cerr << "file decrypt cannot be opened\n";
        exit(1);
    }

    in2 >> fin2 >> fin1;
    fin2 = fin1 - fin2;
    in2.close();

    while (flag) {
        in.seekg(1024 * time, ios::beg);
        time++;
        if (fin1 > 1024) {
            in.read(buffer1, 1024);
            fin1 -= 1024;
            max = 1024;
        }
        else {
            in.read(buffer1, fin1);
            max = fin1;
            flag = false;
        }

        for (k = 0; k < max; k++) {
            pt[i] = buffer1[k];
            i++;
            if (i == 16) {
                i = 0;
                rijndaelDecrypt(rk, Nr, pt, ct);

                for (j = 0; j < 16; j++) {
                    buffer2[p] = ct[j];
                    p++;
                    if (p == 1024) {
                        p = 0;
                        out.write(buffer2, 1024);
                    }
                }
            }
        }
    }

    if (p > 0) {
        out.write(buffer2, p - fin2);
    }
    in.close();
    out.close();
}


