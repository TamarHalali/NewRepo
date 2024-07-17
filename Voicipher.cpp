// Voicipher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//
//#include <cmath>
//#include <fstream>
//#include <iostream>
//#include <vector>
//#include <cstdint>
//#include <sstream>
//#include <string>
//#include <cstring>
//#include "BigInt.h"
//#include "RijndaelAlgFst.h"
//#include "RSA.h"
//#include "AES.h"
//#include "WAVFiles.h"
//#include "AuxiliaryFunctions.h" // Include this header
//#include "DecryptionProcess.h"
//#include "EncryptionProcess.h"
//#include "AudioSteganographyCode.h"
//
//using namespace std;
//
//bool readFileToVector(const std::string& filename, std::vector<uint8_t>& locationsArray) {
//    std::ifstream file(filename, std::ios::binary | std::ios::ate); // Open file in binary mode and move the pointer to the end
//    if (!file) {
//        std::cerr << "Failed to open file: " << filename << std::endl;
//        return false;
//    }
//
//    std::streamsize fileSize = file.tellg(); // Get the size of the file
//    file.seekg(0, std::ios::beg); // Move the pointer back to the beginning
//
//    locationsArray.resize(fileSize); // Resize the vector to hold the file contents
//
//    if (!file.read(reinterpret_cast<char*>(locationsArray.data()), fileSize)) {
//        std::cerr << "Failed to read file: " << filename << std::endl;
//        return false;
//    }
//
//    return true;
//}
//
//int main() {
//    int bitsPerSample = 16;
//    int durationSeconds = 2.5;
//    std::string demoFile = "ringtone.wav";
//    std::string originalFile = "original.wav";
//    std::string outputFilename = "ringtone.wav"; // "steg.wav";
//    std::string dictionaryFilename = "dictionary.txt";
//    std::string locationsArrayFile = "message.txt";
//    int sampleRate, numChannels;
//    std::vector<uint8_t> originalAsBytes = readWAV1(originalFile, sampleRate, numChannels);
//    std::vector<uint8_t> demoAsBytes = readWAV1(demoFile, sampleRate, numChannels);
//    cout << "1 created arrays!" << endl;
//    if (originalAsBytes.empty() || demoAsBytes.empty()) {
//        std::cerr << "Failed to read WAV files." << std::endl;
//        return 1;
//    }
//    std::vector<int> byteMap = createDictionary(demoAsBytes, dictionaryFilename);
//    cout << "2 create bytemap and write bytes to a file" << endl;
//    // מערך המיקומים
//    std::vector<int> locationsArray = writeBytesLocationsFromDemoArray2(originalAsBytes, dictionaryFilename);
//    // הצפנה של AES על מערך המיקומים locationsArray
//    writeIntArrayToFile(locationsArray, locationsArrayFile);
//    Enc();
//
//    std::ifstream cipherTXT("cipher.txt", std::ios::in);
//    if (!cipherTXT) {
//        std::cerr << "file cipher cannot be opened\n";
//        exit(1);
//    }
//
//    std::string cipher; // = readFileIntoString(key);
//    std::string line;
//    while (std::getline(cipherTXT, line)) {
//        cipher += line + "\n";
//    }
//
//    // הסר את השורה האחרונה שנוספה:
//    if (!cipher.empty()) {
//        cipher.pop_back();
//    }
//
//    hideMessageInAudio(demoAsBytes, cipher);
//    writeWAV1(outputFilename, demoAsBytes, sampleRate, numChannels);
//    std::vector<uint8_t> extractedSamples = readWAV1(outputFilename, sampleRate, numChannels);
//    std::string extractedMessage = audioToMessage(extractedSamples, cipher.size());
//
//    std::ifstream keyFile("keyToRSA.txt", std::ios::in);
//    if (!keyFile) {
//        std::cerr << "file keyToRSA cannot be opened\n";
//        exit(1);
//    }
//
//    std::string key;
//    std::string line1;
//    while (std::getline(keyFile, line1)) {
//        key += line1 + "\n";
//    }
//
//    // הסר את השורה האחרונה שנוספה:
//    if (!key.empty()) {
//        key.pop_back();
//    }
//    splitStringToBytes(key);
//    Dec();
//
//    std::vector<uint8_t> locationsArrayToFile;
//    if (readFileToVector("decrypt.txt", locationsArrayToFile)) {
//        std::cout << "File read successfully. Size: " << locationsArrayToFile.size() << " bytes" << std::endl;
//
//        // Optional: Print the content as characters
//        for (uint8_t byte : locationsArrayToFile) {
//            std::cout << byte;
//        }
//        std::cout << std::endl;
//    }
//
//    // המערך הבא מכיל את הקובץ המקורי בבייטים לאחר שחזור ממערך המיקומים
//    std::vector<uint8_t> arrayToWav = writeBytesFromLocationsArrayToBytesArray(locationsArrayToFile, demoAsBytes);
//
//    cout << "5 try to create wav file" << endl;
//    writeWAV("test.wav", arrayToWav, sampleRate, numChannels, bitsPerSample);
//    return 0;
//}
//
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
//bool readFileToVector(const std::string& filename, std::vector<uint8_t>& locationsArray) {
//    std::ifstream file(filename, std::ios::binary | std::ios::ate); // Open file in binary mode and move the pointer to the end
//    if (!file.is_open()) {
//        std::cerr << "Failed to open file: " << filename << std::endl;
//        return false;
//    }
//
//    std::streamsize fileSize = file.tellg(); // Get the size of the file
//    file.seekg(0, std::ios::beg); // Move the pointer back to the beginning
//
//    locationsArray.resize(fileSize); // Resize the vector to hold the file contents
//
//    if (!file.read(reinterpret_cast<char*>(locationsArray.data(), fileSize))) {
//        std::cerr << "Failed to read file: " << filename << std::endl;
//        return false;
//    }
//
//    return true;
//}
//

//bool readFileToVector(const std::string& filename, std::vector<uint8_t>& locationsArray) {
//    std::ifstream file(filename, std::ios::binary | std::ios::ate); // Open file in binary mode and move the pointer to the end
//    if (!file) {
//        std::cerr << "Failed to open file: " << filename << std::endl;
//        return false;
//    }
//
//    std::streamsize fileSize = file.tellg(); // Get the size of the file
//    file.seekg(0, std::ios::beg); // Move the pointer back to the beginning
//
//    locationsArray.resize(fileSize); // Resize the vector to hold the file contents
//
//    if (!file.read(reinterpret_cast<char*>(locationsArray.data()), fileSize)) {
//        std::cerr << "Failed to read file: " << filename << std::endl;
//        return false;
//    }
//
//    return true;
//}


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
    std::string outputFilename ="steg.wav";
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
    for (size_t i = 0; i < 20; i++)
    {
        cout << byteMap[i];
    }
   
    cout << "2 create bytemap and write bytes to a file" << endl;
    //מערך המיקומים
    std::vector<int> locationsArray = writeBytesLocationsFromDemoArray2(originalAsBytes, dictionaryFilename);
    //הצפנה של AES על מערך המיקומים locationsArray
    writeIntArrayToFile(locationsArray, locationsArrayFile);
    Enc();

    std::ifstream cipherTXT("cipher.txt", std::ios::in);
    if (!cipherTXT) {
        std::cerr << "file cipher cannot be opened\n";
        exit(1);
    }

    std::string cipher;//= readFileIntoString(key);
    std::string line;
    while (std::getline(cipherTXT, line)) {
        cipher += line + "\n";
    }

    // הסר את השורה האחרונה שנוספה:
    if (!cipher.empty()) {
        cipher.pop_back();
    }

    hideMessageInAudio(demoAsBytes, cipher);
   // writeWAV1(outputFilename, demoAsBytes, sampleRate, numChannels);
    writeWAV(outputFilename, demoAsBytes, sampleRate, numChannels, bitsPerSample);
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


    //extractedMessage=cipher
    std::ifstream keyFile("keyToRSA.txt", std::ios::in);
    if (!keyFile) {
        std::cerr << "file keyToRSA cannot be opened\n";
        exit(1);
    }

    std::string key;
    std::string line1;
    while (std::getline(keyFile, line1)) {
        key += line1 + "\n";
    }

    // הסר את השורה האחרונה שנוספה:
    if (!key.empty()) {
        key.pop_back();
    }
   splitStringToBytes(key);
    Dec();//replace cipher to extract message that i have to  enter to another file
    // 
   // EncRSA();
    // DecRSA();
    //מערך המיקומים מפוענח
   std::vector<int> locationsArrayDecrypted = readFileLinesAsInts("decrypt.txt");
   for (size_t i = 0; i < 20; i++)
   {
       cout << locationsArrayDecrypted[i]; cout << "\n";
   }
   // המערך הבא מכיל את הקובץ המקורי בבייטים לאחר שחזור ממערך המיקומים
    std::vector<uint8_t> arrayToWav = writeBytesFromLocationsArrayToBytesArray(locationsArrayDecrypted, demoAsBytes);
    cout << "5 try to create wav file"<<endl;
    writeWAV("test.wav", arrayToWav, sampleRate, numChannels, bitsPerSample);
    return 0;
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
