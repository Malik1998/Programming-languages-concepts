//
// Created by user on 14.10.18.
//

#ifndef PROCESSOR_CODETOWORDCONVERTER_H
#define PROCESSOR_CODETOWORDCONVERTER_H

#include <map>
#include "string"

namespace CodeToWordConverter {
    enum ErrorCode {
        FAIL,
        OK
    };

    ErrorCode convert(char* program, char* filename = (char *)"WordProgram.code");
    std::map<int, int>  getLabels(char* program, std::map<int, std::string> &dataVal);
    void writeData(std::ofstream& out, std::map<int, std::string> &dataVal);
    void skipData(char* program, int& currentPosition, std::map<int, std::string> &dataVal);

};


#endif //PROCESSOR_CODETOWORDCONVERTER_H
