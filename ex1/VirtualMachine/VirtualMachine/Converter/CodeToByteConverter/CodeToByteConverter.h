//
// Created by user on 14.10.18.
//

#ifndef PROCESSOR_CODETOBYTECONVERTER_H
#define PROCESSOR_CODETOBYTECONVERTER_H


#include <map>

namespace CodeToByteConverter {
    enum ErrorCode {
        FAIL,
        OK
    };

    static const char* filename = "Byte.code";

    static int const version = 1998;

    std::map<int, int>  getLabels(char* program, std::map<int, std::string> &dataVal, std::map<int, int> &dataPos);
    ErrorCode convert(char* program, char* filename_ = const_cast<char *>("Byte.code"));

    void writeData(std::ofstream& out, std::map<int, std::string> &dataVal, std::map<int, int> &dataPos);
    void skipData(char* program, int& currentPosition, int& currentLine, std::map<int, std::string> &dataVal, std::map<int, int> &dataPos);
};


#endif //PROCESSOR_CODETOBYTECONVERTER_H
