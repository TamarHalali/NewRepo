// Voicipher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
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
#include "AudioSteganographyCode.h"

using namespace std;

int main() {
    //generate keys
    // לשמור את הפרטי
    // את הציבורי לשלוח עם הקובץ
   /* int sampleRate = 44100;
    int numChannels = 2;*/
    int bitsPerSample = 16;
    int durationSeconds = 2.5;
    std::string demoFile = "ringtone.wav";
    std::string originalFile = "original.wav";
    std::string outputFilename = "steg.wav";
    std::string dictionaryFilename = "dictionary.txt";
    std::string locationsArrayFile = "message.txt";
    int sampleRate, numChannels;
    std::vector<uint8_t> originalAsBytes = readWAV1(originalFile, sampleRate, numChannels);
    std::vector<uint8_t> demoAsBytes = readWAV1(demoFile, sampleRate, numChannels);
    cout << "1 created arrays!" << endl;
    if (originalAsBytes.empty() || demoAsBytes.empty()) {
        std::cerr << "Failed to read WAV files." << std::endl;
        return 1;
    }
    std::vector<int> byteMap = createDictionary(demoAsBytes, dictionaryFilename);
    cout << "2 create bytemap and write bytes to a file" << endl;
    //מערך המיקומים
    std::vector<int> locationsArray = writeBytesLocationsFromDemoArray2(originalAsBytes, dictionaryFilename);
    //הצפנה של AES על מערך המיקומים locationsArray
    writeIntArrayToFile(locationsArray, locationsArrayFile);
    Enc();
    std::string cipher;//= readFileIntoString(key);
    ifstream cipherTXT("cipher.txt", ios::in);
    if (!cipherTXT) {
        cerr << "file cipher cannot be opened\n";
        exit(1);
    }
    cipherTXT >> cipher;

    hideMessageInAudio(demoAsBytes, cipher);
    writeWAV1(outputFilename, demoAsBytes, sampleRate, numChannels);
    std::vector<uint8_t> extractedSamples = readWAV1(outputFilename, sampleRate, numChannels);
    std::string extractedMessage = audioToMessage(extractedSamples, cipher.size());
    //string s;
    //ifstream keyFile("keyToRSA.txt", ios::in);
    //if (!keyFile) {
    //    cerr << "file key.txt cannot be opened\n";
    //    exit(1);
    //}
    //getline(keyFile, s);
    //keyFile.close();
    //splitStringToBytes(s);
   // ofstream out("key.txt", ios::out);
   // if (!out) {
   //     cerr << "file  cannot be opened\n";
   //     exit(1);
   // }
   //out<< extractedMessage;
    ifstream keyFile("keyToRSA.txt", ios::in);
    if (!keyFile) {
        cerr << "file key.txt cannot be opened\n";
        exit(1);
    }
    std::string key;
    keyFile >> key;
   splitStringToBytes(key);
    Dec();
    // 
   // EncRSA();
    // DecRSA();
    //הצפנה של מפתח AES עם RSA

    //סטגנוגרפיה לתוך קובץ הדמה

    //שליחת קובץ הסטג + מפתח ההצפנה של AES המוצפן

   
    ////המערך הבא מכיל את הקובץ המקורי בבייטים לאחר שחזור ממערך המיקומים
    //std::vector<uint8_t> arrayToWav = writeBytesFromLocationsArrayToBytesArray(locationsArray, demoAsBytes);


    //cout << "5 try to create wav file"<<endl;
    //writeWAV("test.wav", arrayToWav, sampleRate, numChannels, bitsPerSample);
    //return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
