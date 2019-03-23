//
// Created by user on 13.10.18.
//

#ifndef PROCESSOR_PROCESSOR_H
#define PROCESSOR_PROCESSOR_H

#include <iostream>
#include "SafeStack/SafeStack.h"
#include "CommandService/CommandService.h"
#define MAX_LINE_SIZE 256

#define SIZE_OF_STACK 100

class Processor {
private:
    SafeStack<int> stack;
    SafeStack<int> stackOfCalls;
    char* programm;
    int sizeOfProgram;
    std::istream& cin;
    std::ostream& cout;
    int rax, rbx, rcx, rdx;

    static const int RAM_SIZE = 1024;
    int ram[RAM_SIZE];

    char additionalStack[MAX_LINE_SIZE];

public:
    enum TypeOfProgram {
        BYTECODE,
        DECODED_COMMANDS,
        WORD_COMMANDS
    };

    enum AnswerFromServe {
        OK,
        READ,
        WRITE,
        END
    };

   // ProcessorTest(std::istream& in, TypeOfProgram typeOfProgram);
    Processor(char* filename, TypeOfProgram typeOfProgram, std::istream& in = std::cin, std::ostream& out = std::cout);
    void execute();

private:
    void conditionalJump(int *i, CommandService::Command command);
    void printString(int *i);
    int getNumber(char *string);
    int getNumberChar(char *string, int length);
    void getDataPlace();
    void skipData(int &i);

    int dataPlace;
};


#endif //PROCESSOR_PROCESSOR_H
