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

    std::map<int, int>  getLabels(char* program);
    ErrorCode convert(char* program, char* filename_ = const_cast<char *>("Byte.code"));
};


#endif //PROCESSOR_CODETOBYTECONVERTER_H
