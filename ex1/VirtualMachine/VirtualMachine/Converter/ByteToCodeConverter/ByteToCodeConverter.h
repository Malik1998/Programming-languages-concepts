//
// Created by user on 14.10.18.
//

#ifndef PROCESSOR_BYTETOCODECONVERTER_H
#define PROCESSOR_BYTETOCODECONVERTER_H


#include <cstddef>
#include <map>

namespace ByteToCodeConverter {
    enum ErrorCode {
        FAIL,
        OK
    };

    static const char* filename = "Byte.code";


    ErrorCode convert(char* program, char* filename_ = const_cast<char *>("Code.code"), int length = 0);
    std::map<int, int>  getLabels(char* program, int length, std::map<int, std::string> &dataVal, std::map<int, int> &dataPos);
    int getNumber(char *strin);

    void writeData(std::ofstream& out, std::map<int, std::string> &dataVal, std::map<int, int> &dataPos);
    void skipData(char* program, int& currentPosition, std::map<int, std::string> &dataVal, std::map<int, int> &dataPos);
};


#endif //PROCESSOR_BYTETOCODECONVERTER_H
