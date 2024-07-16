#pragma once
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>
#include <sstream>
#include <string>
#include <cstring>
#include "RijndaelAlgFst.h"

using namespace std;

void splitStringToBytes(string key);
void generateRandomKey(u8* key, int length);
void Enc();
void Dec();