#include <iostream>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>
#include <sstream>
#include <string>
#include <cstring>
#include "AuxiliaryFunctions.h"

using namespace std;

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

std::vector<int> readFileLinesAsInts(const std::string& fileName) {
	std::ifstream file(fileName);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open the file.");
	}

	std::vector<int> lines;
	std::string line;

	while (std::getline(file, line)) {
		try {
			lines.push_back(std::stoi(line));
		}
		catch (const std::invalid_argument& e) {
			throw std::runtime_error("The line does not contain a valid integer.");
		}
		catch (const std::out_of_range& e) {
			throw std::runtime_error("The integer is out of range.");
		}
	}

	file.close();
	return lines;
}

// יצירת מערך המיקומים 
std::vector<int> writeBytesLocationsFromDemoArray2(const std::vector<uint8_t>& originalAsBytes, const std::string& file) {
	std::vector<int> arrayToWav(originalAsBytes.size());
	cout << "3. start write location array to int array:" << endl;
	cout << "size of location array is: " << originalAsBytes.size() << endl;

	// קריאת כל השורות מהקובץ מראש ושמירתן במערך בזיכרון
	std::vector<int> fileLines = readFileLinesAsInts(file);

	for (size_t i = 0; i < originalAsBytes.size(); i++) {
		int result = fileLines[originalAsBytes[i]];
		arrayToWav[i] = result;
	}

	cout << "3 finish write location array!!!!!!" << endl;
	return arrayToWav;
}

//פונקציה המקבלת את מערך המיקומים ואת קובץ הדמה - ןיוצרת את הקובץ המקורי
std::vector<uint8_t> writeBytesFromLocationsArrayToBytesArray(const std::vector<int>& locationsArray, const std::vector<uint8_t>& demoAsBytes) {
	int size = locationsArray.size();
	std::vector<uint8_t> arrayToWav(size);
	cout << " 4. start write location array to bytes!!:" << endl;
	for (size_t i = 0; i < size; i++) {
		arrayToWav[i] = demoAsBytes[locationsArray[i]];
	}
	cout << " 4. finish write location array to bytes!!!!" << endl;
	return arrayToWav;
}

//the long functions......
//int readLineAsInt(const std::string& fileName, int lineIndex) {
//    std::ifstream file(fileName);
//    if (!file.is_open()) {
//        throw std::runtime_error("Could not open the file.");
//    }
//    std::string line;
//    int currentLineIndex = 0;
//
//    // קריאת השורות מהקובץ
//    while (std::getline(file, line)) {
//        if (currentLineIndex == lineIndex) {
//            // סגירת הקובץ
//            file.close();
//            try {
//                // המרת השורה למספר שלם והחזרת התוצאה
//                return std::stoi(line);
//            }
//            catch (const std::invalid_argument& e) {
//                throw std::runtime_error("The line does not contain a valid integer.");
//            }
//            catch (const std::out_of_range& e) {
//                throw std::runtime_error("The integer is out of range.");
//            }
//        }
//        currentLineIndex++;
//    }
//
//    // סגירת הקובץ
//    file.close();
//    throw std::out_of_range("The line index is out of range.");
//}
////יצירת מערך של בייטים מקובץ המילון המכיל מיקומים מקובץ הדמה
//std::vector<uint8_t> writeBytesFromTextToArray(const std::vector<uint8_t>& originalAsBytes, const std::vector<uint8_t>& demoAsBytes, std::string file) {
//    std::vector<uint8_t> arrayToWav(originalAsBytes.size());
//
//    for (size_t i = 0; i < originalAsBytes.size(); i++) {
//        int result = readLineAsInt(file, static_cast<int>(originalAsBytes[i]));
//        arrayToWav[i] = demoAsBytes[result];
//    }
//    return arrayToWav;
//}
////ארוך בגלל הגישות לקובץ
////פונקציה היוצרת את מערך המיקומים
////file=dictionary
////הסרתי את קובץ הדמה מקבלה כפרמטר - לא צריך אותו
////  const std::vector<uint8_t>& demoAsBytes,
//std::vector<int> writeBytesLocationsFromDemoArray(const std::vector<uint8_t>& originalAsBytes, std::string file) {
//    std::vector<int> arrayToWav(originalAsBytes.size());
//    cout << "3. start write location array to int arrrray:" << endl;
//    cout << "size of location array is:"<< originalAsBytes.size() << endl;
//    for (size_t i = 0; i < originalAsBytes.size(); i++) {
//        int result = readLineAsInt(file, static_cast<int>(originalAsBytes[i]));
//        arrayToWav[i] = result;
//    }
//    cout << "3 finish write location array!!!!!!" << endl;
//    return arrayToWav;
//}

//