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
    std::map<int, int>  getLabels(char* program, int length);
    int getNumber(char *strin);
};


#endif //PROCESSOR_BYTETOCODECONVERTER_H
