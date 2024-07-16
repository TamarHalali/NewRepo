#pragma once
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>
#include <sstream>
#include <string>
#include <cstring>

void writeWAV(const std::string& filename, const std::vector<uint8_t>& audioData, int sampleRate, int numChannels, int bitsPerSample);
std::vector<uint8_t> readWAV(const std::string& filename);