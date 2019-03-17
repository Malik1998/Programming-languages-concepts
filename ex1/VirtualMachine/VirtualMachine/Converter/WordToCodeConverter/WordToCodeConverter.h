//
// Created by user on 13.10.18.
//

#ifndef PROCESSOR_WORDTOCODECONVERTER_H
#define PROCESSOR_WORDTOCODECONVERTER_H


#include <fstream>
#include "../../CommandService/CommandService.h"
#include <map>

namespace WordToCodeConverter {

    enum ErrorCode {
        FAIL,
        OK
    };

    static const char* filename = "CodeProgram.code";

    std::map<std::string, int>  getLabels(char* program);
    ErrorCode convert(char* program, char* filename_ = const_cast<char *>("CodeProgram.code"));

};


#endif //PROCESSOR_WORDTOCODECONVERTER_H
