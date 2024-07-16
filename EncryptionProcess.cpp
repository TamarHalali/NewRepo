#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>
#include <sstream>
#include <string>
#include <cstring>
#include "BigInt.h"
#include "RijndaelAlgFst.h"
#include "RSA.h"
#include "AES.h"
#include "WAVFiles.h"
#include "AuxiliaryFunctions.h"
#include "DecryptionProcess.h"
#include "EncryptionProcess.h"

using namespace std;



void doing() {
    int sampleRate = 44100;
    int numChannels = 2;
    int bitsPerSample = 16;
    int durationSeconds = 2.5;
    std::string demoFile = "ringtone.wav";
    std::string originalFile = "original.wav";
    std::string dictionaryFilename = "dictionary.txt";
    std::string locationsArrayFile = "message.txt";
    //std::vector<uint8_t> originalAsBytes = readWAV(originalFile);
    //std::vector<uint8_t> demoAsBytes = readWAV(demoFile);
    //std::vector<int> byteMap = createDictionary(demoAsBytes, dictionaryFilename);
    //std::vector<int> locationsArray = writeBytesLocationsFromDemoArray2(originalAsBytes, dictionaryFilename);
    //writeIntArrayToFile(locationsArray, locationsArrayFile);
    //Enc();
    ////הצפנה של מפתח AES עם RSA


    //string message;
    //ifstream keyFile("keyToRSA.txt", ios::in);
    //if (!keyFile) {
    //    cerr << "file key.txt cannot be opened\n";
    //    exit(1);
    //}
    //getline(keyFile, message);
    //keyFile.close();
    //e = public key---
    //n = from db
    //EncRSA(message, e, n);
    //DecRSA( cipher, d, n);


        //סטגנוגרפיה לתוך קובץ הדמה

        //שליחת קובץ הסטג + מפתח ההצפנה של AES המוצפן


        ////המערך הבא מכיל את הקובץ המקורי בבייטים לאחר שחזור ממערך המיקומים
        //std::vector<uint8_t> arrayToWav = writeBytesFromLocationsArrayToBytesArray(locationsArray, demoAsBytes);


        //cout << "5 try to create wav file"<<endl;
        //writeWAV("test.wav", arrayToWav, sampleRate, numChannels, bitsPerSample);

}