#pragma once
#ifndef AUDIO_STEGANOGRAPHY_H
#define AUDIO_STEGANOGRAPHY_H

#include <iostream>
#include <vector>
#include <bitset>
#include <string>
//#include <sndfile.h>

void hideMessageInAudio(std::vector<uint8_t>& samples, const std::string& message);
std::string audioToMessage(const std::vector<uint8_t>& samples, size_t messageSize);
//fastest
std::vector<uint8_t> readWAV1(const std::string& filename, int& sampleRate, int& numChannels);
void writeWAV1(const std::string& filename, const std::vector<uint8_t>& samples, int sampleRate, int numChannels);

#endif
