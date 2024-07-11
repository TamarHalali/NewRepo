#pragma once

#include "RijndaelAlgFst.h"
#include<time.h>
#include<fstream>
#include<iostream>

using namespace std;

void generateKey(u8 key[16]);

void Enc();

void Dec();