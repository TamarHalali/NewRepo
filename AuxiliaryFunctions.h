#pragma once
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

void writeIntArrayToFile(const std::vector<int>& intArray, const std::string& filename);
void writeBytesToDictionaryFile(const std::vector<int>& bytes, const std::string& filename);
std::vector<int> createDictionary(const std::vector<uint8_t>& demoAsBytes, const std::string& dictionaryFileName);
std::vector<int> readFileLinesAsInts(const std::string& fileName);
std::vector<int> writeBytesLocationsFromDemoArray2(const std::vector<uint8_t>& originalAsBytes, const std::string& file);// יצירת מערך המיקומים 
std::vector<uint8_t> writeBytesFromLocationsArrayToBytesArray(const std::vector<int>& locationsArray, const std::vector<uint8_t>& demoAsBytes);