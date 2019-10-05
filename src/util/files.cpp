//
// Created by Júlio César Lopes on 02/10/19.
//

#include "files.h"

std::string getStringFromFile(const char* filePath) {
    std::ifstream fStream(filePath);
    std::stringstream sStream;
    sStream << fStream.rdbuf();

    fStream.close();

    const std::basic_string bString = sStream.str();

    return bString;
}
