#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>
#include <sstream>
#include <string>
#include <cstring>
#include "WAVFiles.h"
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