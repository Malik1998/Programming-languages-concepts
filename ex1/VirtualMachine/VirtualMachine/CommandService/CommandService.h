//
// Created by user on 14.10.18.
//


#ifndef PROCESSOR_COMMANDSERVICE_H
#define PROCESSOR_COMMANDSERVICE_H

#include <iosfwd>
#include <string>
#define MAX_LENGTH 500



namespace CommandService {

    static const int number_of_commands = 19;

    static char commandChar[MAX_LENGTH];

    enum Command {
        push = 0,
        pop = 1,
        add = 2,
        sub = 3,
        multiply = 4,
        divi = 5,
        in = 6,
        out = 7,
        end = 8,
        jmp = 9,
        ja = 10,
        je = 11,
        label = 12,
        sqrt = 13,
        ret = 14,
        call = 15,
        print = 16,
        data = 17,
        no_such_command = 18
    };

    enum TypeOfMemory {
        RAM,
        STACK,
        RAX,
        RBX,
        RCX,
        RDX
    };

    static const char* commands[number_of_commands] = {
            "push",
            "pop",
            "add",
            "sub",
            "multiply",
            "div",
            "in",
            "out",
            "end",
            "jmp",
            "ja",
            "je",
            "label",
            "sqrt",
            "ret",
            "call",
            "print",
            ".data",
            "no_such_command"
    };

    std::pair<Command, int> extractCommandWord(char *in);
    std::pair<Command, int> extractCommandCode(char *in);
    std::pair<Command, int> extractCommandByte(char *in);
    std::pair<TypeOfMemory, int> getTypeOfMemory(char *in);
    std::pair<std::string, int> extractWord(char* program, int length = -1);
    std::pair<std::string, int> extractWordByte(char* program);
    int extractWordByte(char* program, char* str1);


};


#endif //PROCESSOR_COMMANDSERVICE_H
