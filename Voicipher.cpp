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


using namespace std;
//using namespace little_endian_io;
namespace little_endian_io
{
    template <typename Word>
    std::ostream& write_word(std::ostream& outs, Word value, unsigned size = sizeof(Word))
    {
        for (; size; --size, value >>= 8)
            outs.put(static_cast<char>(value & 0xFF));
        return outs;
    }
}

struct WAVHeader {
    // RIFF Header
    char riffHeader[4]; // "RIFF"
    uint32_t chunkSize; // File size - 8
    char waveHeader[4]; // "WAVE"

    // Format Header
    char fmtHeader[4]; // "fmt "
    uint32_t fmtChunkSize; // 16 for PCM
    uint16_t audioFormat; // 1 for PCM
    uint16_t numChannels; // Number of channels
    uint32_t sampleRate; // Sampling Frequency in Hz
    uint32_t byteRate; // sampleRate * numChannels * bytesPerSample
    uint16_t blockAlign; // numChannels * bytesPerSample
    uint16_t bitsPerSample; // Number of bits per sample

    // Data Header
    char dataHeader[4]; // "data"
    uint32_t dataSize; // NumSamples * numChannels * bytesPerSample
};

void writeWAV(const std::string& filename, const std::vector<uint8_t>& audioData, int sampleRate, int numChannels, int bitsPerSample) {
    WAVHeader header;

    // Fill the RIFF header
    std::memcpy(header.riffHeader, "RIFF", 4);
    std::memcpy(header.waveHeader, "WAVE", 4);

    // Fill the format header
    std::memcpy(header.fmtHeader, "fmt ", 4);
    header.fmtChunkSize = 16; // PCM
    header.audioFormat = 1; // PCM
    header.numChannels = numChannels;
    header.sampleRate = sampleRate;
    header.bitsPerSample = bitsPerSample;
    header.byteRate = sampleRate * numChannels * bitsPerSample / 8;
    header.blockAlign = numChannels * bitsPerSample / 8;

    // Fill the data header
    std::memcpy(header.dataHeader, "data", 4);
    header.dataSize = audioData.size();

    // Calculate the overall file size
    header.chunkSize = 4 + (8 + header.fmtChunkSize) + (8 + header.dataSize);

    // Write the WAV file
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Could not open file for writing: " << filename << std::endl;
        return;
    }
    outFile.write(reinterpret_cast<const char*>(&header), sizeof(WAVHeader));
    outFile.write(reinterpret_cast<const char*>(audioData.data()), audioData.size());
    outFile.close();
}

// פונקציה לקריאת קובץ WAV והחזרתו כמערך של בייטים
std::vector<uint8_t> readWAV(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return {};
    }
    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return buffer;
}

void writeBytesToDictionaryFile(const std::vector<int>& bytes, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Could not open file for writing: " << filename << std::endl;
        return;
    }
    for (int byte : bytes) {
        file << static_cast<int>(byte) << std::endl;
    }
    file.close();
}
//dictionary of 256 keys for all the bytes with the first location its appear in the demo fule
std::vector<int> createDictionary(const std::vector<uint8_t>& demoAsBytes, const std::string& dictionaryFileName) {
    std::vector<int> byteMap(256, -1); // אתחול המערך בגודל 256 עם ערך -1 )
    int count = 0;
    for (size_t i = 0; i < demoAsBytes.size() && count < 256; i++) {
        if (byteMap[demoAsBytes[i]] == -1) { // אם הערך לא מאותחל, נכניס את האינדקס
            byteMap[demoAsBytes[i]] = static_cast<int>(i);
            count++;
        }
    }
    writeBytesToDictionaryFile(byteMap, dictionaryFileName);
    return byteMap;
}

int readLineAsInt(const std::string& fileName, int lineIndex) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open the file.");
    }
    std::string line;
    int currentLineIndex = 0;

    // קריאת השורות מהקובץ
    while (std::getline(file, line)) {
        if (currentLineIndex == lineIndex) {
            // סגירת הקובץ
            file.close();
            try {
                // המרת השורה למספר שלם והחזרת התוצאה
                return std::stoi(line);
            }
            catch (const std::invalid_argument& e) {
                throw std::runtime_error("The line does not contain a valid integer.");
            }
            catch (const std::out_of_range& e) {
                throw std::runtime_error("The integer is out of range.");
            }
        }
        currentLineIndex++;
    }

    // סגירת הקובץ
    file.close();
    throw std::out_of_range("The line index is out of range.");
}
//יצירת מערך של בייטים מקובץ המילון המכיל מיקומים מקובץ הדמה
std::vector<uint8_t> writeBytesFromTextToArray(const std::vector<uint8_t>& originalAsBytes, const std::vector<uint8_t>& demoAsBytes, std::string file) {
    std::vector<uint8_t> arrayToWav(originalAsBytes.size());

    for (size_t i = 0; i < originalAsBytes.size(); i++) {
        int result = readLineAsInt(file, static_cast<int>(originalAsBytes[i]));
        arrayToWav[i] = demoAsBytes[result];
    }
    return arrayToWav;
}
//פונקציה היוצרת את מערך המיקומים
//file=dictionary
//הסרתי את קובץ הדמה מקבלה כפרמטר - לא צריך אותו
//  const std::vector<uint8_t>& demoAsBytes,
std::vector<int> writeBytesLocationsFromDemoArray(const std::vector<uint8_t>& originalAsBytes, std::string file) {
    std::vector<int> arrayToWav(originalAsBytes.size());

    for (size_t i = 0; i < originalAsBytes.size(); i++) {
        int result = readLineAsInt(file, static_cast<int>(originalAsBytes[i]));
        arrayToWav[i] = result;
    }
    return arrayToWav;
}

void writeIntArrayToFile(const std::vector<int>& intArray, const std::string& filename) {
    std::ofstream outputFile(filename);

    if (outputFile.is_open()) {
        for (int i = 0; i < intArray.size(); i++) {
            outputFile << intArray[i] << "\n";
        }

        std::cout << "Array successfully written to file: " << filename << std::endl;
        outputFile.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main() {
    int sampleRate = 44100;
    int numChannels = 2;
    int bitsPerSample = 16;
    int durationSeconds = 2.5;
    std::string demoFile = "ringtone.wav";
    std::string originalFile = "original.wav";
    std::string dictionaryFilename = "dictionary.txt";
    std::string keyFile = "key.txt";
    std::vector<uint8_t> originalAsBytes = readWAV(originalFile);
    std::vector<uint8_t> demoAsBytes = readWAV(demoFile);
    cout << "1 created arrays!" << endl;
    if (originalAsBytes.empty() || demoAsBytes.empty()) {
        std::cerr << "Failed to read WAV files." << std::endl;
        return 1;
    }
    std::vector<int> byteMap = createDictionary(demoAsBytes, dictionaryFilename);
    cout << "2 create bytemap and write bytes to a file" << endl;
    //מערך המיקומים
    std::vector<int> key = writeBytesLocationsFromDemoArray(originalAsBytes, dictionaryFilename);
   //הצפנה של AES
   // Dec();
    //הצפנה של מפתח AES עם RSA

    //סטגנוגרפיה לתוך קובץ הדמה

    //שליחת קובץ הסטג + מפתח ההצפנה של AES המוצפן

    writeIntArrayToFile(key, keyFile);
    //המערך הבא מכיל את הקובץ המקורי מבוטא ע"י המיקומים בקובץ דמה - הוא בעצם המפתח...
    std::vector<uint8_t> arrayToWav = writeBytesFromTextToArray(originalAsBytes, demoAsBytes, dictionaryFilename);


    cout << "4 try to create wav file"<<endl;
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
