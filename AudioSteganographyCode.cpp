#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstring>
#include <cstdint>
#include <sstream>
#include <string>
#include <bitset>
#include <chrono>
#include <thread>
#include <mutex>
#include "AudioSteganographyCode.h"


using namespace std::chrono;
using namespace std;
//מהיר בשתי שניות ממה שמתחתיו
// פונקציה לקריאת קובץ WAV
std::vector<uint8_t> readWAV1(const std::string& filename, int& sampleRate, int& numChannels) {
    std::ifstream file(filename, std::ios::binary);
    std::vector<uint8_t> samples;

    if (file.is_open()) {
        char buffer[4];
        file.seekg(24);
        file.read(buffer, 4);
        sampleRate = *reinterpret_cast<int*>(buffer);
        file.seekg(22);
        file.read(buffer, 2);
        numChannels = *reinterpret_cast<short*>(buffer);

        file.seekg(44);
        while (file.read(buffer, 2)) {
            samples.push_back(*reinterpret_cast<int16_t*>(buffer));
        }
    }

    file.close();
    return samples;
}

// פונקציה לכתיבת קובץ WAV
void writeWAV1(const std::string& filename, const std::vector<uint8_t>& samples, int sampleRate, int numChannels) {
    std::ofstream file(filename, std::ios::binary);

    if (file.is_open()) {
        file.write("RIFF", 4);
        int32_t chunkSize = 36 + samples.size() * 2;
        file.write(reinterpret_cast<char*>(&chunkSize), 4);
        file.write("WAVEfmt ", 8);
        int32_t subChunk1Size = 16;
        file.write(reinterpret_cast<char*>(&subChunk1Size), 4);
        int16_t audioFormat = 1;
        file.write(reinterpret_cast<char*>(&audioFormat), 2);
        file.write(reinterpret_cast<char*>(&numChannels), 2);
        file.write(reinterpret_cast<char*>(&sampleRate), 4);
        int32_t byteRate = sampleRate * numChannels * 2;
        file.write(reinterpret_cast<char*>(&byteRate), 4);
        int16_t blockAlign = numChannels * 2;
        file.write(reinterpret_cast<char*>(&blockAlign), 2);
        int16_t bitsPerSample = 16;
        file.write(reinterpret_cast<char*>(&bitsPerSample), 2);
        file.write("data", 4);
        int32_t dataChunkSize = samples.size() * 2;
        file.write(reinterpret_cast<char*>(&dataChunkSize), 4);
        file.write(reinterpret_cast<const char*>(samples.data()), samples.size() * 2);
    }

    file.close();
}
void hideMessageInAudio(std::vector<uint8_t>& samples, const std::string& message) {
    size_t messageIndex = 0;
    size_t bitIndex = 0;

    for (size_t i = 0; i < samples.size() && messageIndex < message.size(); ++i) {
        if (i % 8 == 0) { // להשתמש בכל שמונה דגימות
            int8_t bit = (message[messageIndex] >> bitIndex) & 1;
            samples[i] = (samples[i] & ~1) | bit; // להחליף את הביט האחרון בדגימה
            bitIndex++;
            if (bitIndex == 8) {
                bitIndex = 0;
                messageIndex++;
            }
        }
    }
}
std::string audioToMessage(const std::vector<uint8_t>& samples, size_t messageSize) {
    std::string message(messageSize, '\0');
    size_t messageIndex = 0;
    size_t bitIndex = 0;

    for (size_t i = 0; i < samples.size() && messageIndex < messageSize; ++i) {
        if (i % 8 == 0) { // להשתמש בכל שמונה דגימות
            int8_t bit = samples[i] & 1; // לחלץ את הביט האחרון
            message[messageIndex] |= (bit << bitIndex);
            bitIndex++;
            if (bitIndex == 8) {
                bitIndex = 0;
                messageIndex++;
            }
        }
    }

    return message;
}


int main2() {
    std::string inputFilename = R"(C:\Users\USER\Desktop\Project\Project\trySteg2\Titanium_Pavane_PianoCello_Cover.wav)";
    std::string outputFilename = "try555file.wav";
    std::string key = "newLong.txt";
    std::cout << "start key!!" << std::endl;
    auto start = high_resolution_clock::now();
    std::string message;//= readFileIntoString(key);
    auto end = high_resolution_clock::now();
    std::cout << "finish key!!" << std::endl;
    std::cout << "Reading key took: " << duration_cast<milliseconds>(end - start).count() << " ms" << std::endl;


    int sampleRate, numChannels;
  //  std::vector<int16_t> samples = readWAV1(inputFilename, sampleRate, numChannels);

    //size_t requiredSamples = message.size() * 8;
    //if (requiredSamples > samples.size()) {
    //    std::cerr << "Error: The message is too large to be embedded in the given WAV file." << std::endl;
    //    return 1;
    //}
  /*  hideMessageInAudio(samples, message);
    writeWAV1(outputFilename, samples, sampleRate, numChannels);
    std::vector<int16_t> extractedSamples = readWAV1(outputFilename, sampleRate, numChannels);
    std::string extractedMessage = audioToMessage(extractedSamples, message.size());*/
    //  std::cout << "Extracted message: " << extractedMessage << std::endl;
    return 0;
}
//
// פונקצית עזר שלא בטוח שאני צריכה...
// std::string readFileIntoString(const std::string& fileName) {
//std::ifstream fileStream(fileName, std::ios::in | std::ios::binary);
//if (!fileStream) {
//    throw std::runtime_error("Could not open file: " + fileName);
//}
//
//std::ostringstream ss;
//ss << fileStream.rdbuf();
//return ss.str();
//}
// 
//------------------------------------------------------------------
// 
// fit-to book
//--------------------------------------------------
// #include "WAVFiles.h"

//void hideMessageInAudio(std::vector<uint8_t>& audioData, const std::string& message) {
//    size_t messageIndex = 0;
//    size_t bitIndex = 0;
//
//    for (size_t i = sizeof(WAVHeader); i < audioData.size() && messageIndex < message.size(); ++i) {
//        if ((i - sizeof(WAVHeader)) % 8 == 0) {
//            uint8_t bit = (message[messageIndex] >> bitIndex) & 1;
//            audioData[i] = (audioData[i] & ~1) | bit;
//            bitIndex++;
//            if (bitIndex == 8) {
//                bitIndex = 0;
//                messageIndex++;
//            }
//        }
//    }
//}
//
//std::string extractMessage(const std::vector<uint8_t>& audioData, size_t messageSize) {
//    std::string message(messageSize, '\0');
//    size_t messageIndex = 0;
//    size_t bitIndex = 0;
//
//    for (size_t i = sizeof(WAVHeader); i < audioData.size() && messageIndex < messageSize; ++i) {
//        if ((i - sizeof(WAVHeader)) % 8 == 0) {
//            uint8_t bit = audioData[i] & 1;
//            message[messageIndex] |= (bit << bitIndex);
//            bitIndex++;
//            if (bitIndex == 8) {
//                bitIndex = 0;
//                messageIndex++;
//            }
//        }
//    }
//
//    return message;
//}
//
//std::string readFileIntoString(const std::string& fileName) {
//    std::ifstream fileStream(fileName, std::ios::in | std::ios::binary);
//    if (!fileStream) {
//        throw std::runtime_error("Could not open file: " + fileName);
//    }
//
//    std::ostringstream ss;
//    ss << fileStream.rdbuf();
//    return ss.str();
//}
//
//int main() {
//    std::string inputFilename = R"(C:\Users\USER\Desktop\Project\Project\trySteg2\Titanium_Pavane_PianoCello_Cover.wav)";
//    std::string outputFilename = "try444file.wav";
//    std::string key = "newLong.txt";
//    std::cout << "start key!!" << std::endl;
//    auto start = high_resolution_clock::now();
//    std::string message = readFileIntoString(key);
//    auto end = high_resolution_clock::now();
//    std::cout << "finish key!!" << std::endl;
//    std::cout << "Reading key took: " << duration_cast<milliseconds>(end - start).count() << " ms" << std::endl;
//    
//    std::vector<uint8_t> audioData = readWAV(inputFilename);
//
//    WAVHeader* header = reinterpret_cast<WAVHeader*>(audioData.data());
//    int sampleRate = header->sampleRate;
//    int numChannels = header->numChannels;
//    int bitsPerSample = header->bitsPerSample;
//
//    //size_t requiredSamples = message.size() * 8;
//    //if (requiredSamples > audioData.size() - sizeof(WAVHeader)) {
//    //    std::cerr << "Error: The message is too large to be embedded in the given WAV file." << std::endl;
//    //    return 1;
//    //}
//
//    hideMessageInAudio(audioData, message);
//    writeWAV(outputFilename, audioData, sampleRate, numChannels, bitsPerSample);
//
//   std::vector<uint8_t> extractedAudioData = readWAV(outputFilename);
//    std::string extractedMessage = extractMessage(extractedAudioData, message.size());
//    cout << "text size:" << message.size() << endl;
//    //cout << "extractedMessage size:" << extractedMessage.size() << endl;
//   // std::cout << "Extracted message: " << extractedMessage << std::endl;
//    return 0;
//}
//------------------------------------------------------------------
// #include <sndfile.h>
//original - too long
//// Converts a string message to a vector of bits.
//std::vector<bool> stringToBinary(const std::string& message) {
//    std::vector<bool> binaryMessage;
//    for (char c : message) {
//        std::bitset<8> charBits(c);
//        for (int i = 7; i >= 0; --i) {
//            binaryMessage.push_back(charBits.test(i));
//        }
//    }
//    return binaryMessage;
//}
//
//// Embeds the binary message into the LSB of each audio sample.
//bool hideMessageInAudio(const std::string& audioFilePath, const std::string& outputFilePath, const std::string& message) {
//    std::vector<bool> binaryMessage = stringToBinary(message + "\0"); // Include null terminator for the message.
//
//    SF_INFO sfinfo;
//    SNDFILE* sndfile = sf_open(audioFilePath.c_str(), SFM_READ, &sfinfo);
//    if (!sndfile) {
//        std::cerr << "Failed to open input file." << std::endl;
//        return false;
//    }
//
//    std::vector<short> samples(sfinfo.frames * sfinfo.channels);
//    if (sf_read_short(sndfile, samples.data(), samples.size()) != samples.size()) {
//        sf_close(sndfile);
//        std::cerr << "Failed to read audio data." << std::endl;
//        return false;
//    }
//    sf_close(sndfile);
//
//    if (samples.size() < binaryMessage.size()) {
//        std::cerr << "Audio file too short for the message." << std::endl;
//        return false;
//    }
//
//    // Embed the message into the LSB of samples.
//    for (size_t i = 0; i < binaryMessage.size(); ++i) {
//        if (binaryMessage[i]) {
//            samples[i] |= 1; // Set LSB to 1 if bit is 1.
//        }
//        else {
//            samples[i] &= ~1; // Set LSB to 0 if bit is 0.
//        }
//    }
//
//    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16; // Ensure the format is appropriate for the output.
//
//    sndfile = sf_open(outputFilePath.c_str(), SFM_WRITE, &sfinfo);
//    if (!sndfile) {
//        std::cerr << "Failed to open output file." << std::endl;
//        return false;
//    }
//
//    if (sf_write_short(sndfile, samples.data(), samples.size()) != samples.size()) {
//        sf_close(sndfile);
//        std::cerr << "Failed to write modified audio data." << std::endl;
//        return false;
//    }
//
//    sf_close(sndfile);
//    return true;
//}
//
//std::string audioToMessage(const std::string& filePath) {
//    SF_INFO sfinfo;
//    SNDFILE* sndfile = sf_open(filePath.c_str(), SFM_READ, &sfinfo);
//    if (!sndfile) {
//        std::cerr << "Failed to open input file." << std::endl;
//        return "";
//    }
//
//    std::vector<short> samples(sfinfo.frames * sfinfo.channels);
//    if (sf_read_short(sndfile, samples.data(), samples.size()) != samples.size()) {
//        sf_close(sndfile);
//        std::cerr << "Failed to read audio data." << std::endl;
//        return "";
//    }
//    sf_close(sndfile);
//
//    std::string message;
//    std::bitset<8> charBits;
//    size_t bitIndex = 0;
//
//    for (size_t i = 0; i < samples.size(); ++i) {
//        charBits[7 - bitIndex] = (samples[i] & 1) != 0; // Extract the LSB from the sample.
//
//        bitIndex++;
//        if (bitIndex == 8) { // Once we have 8 bits, convert to character.
//            char character = static_cast<char>(charBits.to_ulong());
//            if (character == '\0') break;
//            message += character;
//            bitIndex = 0;
//            charBits.reset();
//        }
//    }
//
//    return message;
//}

