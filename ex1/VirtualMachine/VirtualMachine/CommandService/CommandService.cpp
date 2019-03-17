//
// Created by user on 14.10.18.
//

#include <cstring>
#include "CommandService.h"

namespace CommandService {

    std::pair<std::string, int> extractWord(char* program, int length) {
        if (length != -1) {
            return std::make_pair(std::string(program).substr(0, length), length);
        }
        int position = 0;
        if (program[1] == '\"') {
            sscanf(program + 2, "%[^\"]\"%n", commandChar, &position);
            position += 2;
        } else {
            sscanf(program, "%s%n", commandChar, &position);
        }
        return std::make_pair(commandChar, position);
    }

    std::pair<Command, int> extractCommandWord(char *in) {
        int position = 0;
        sscanf(in, "%s%n", commandChar, &position);
        for (int i = 0; i < number_of_commands; i++) {
            if (std::strcmp(commands[i], commandChar) == 0) {
                return std::make_pair(static_cast<Command>(i), position);
            }
        }
        if (commandChar[strlen(commandChar) - 1] == ':') {
            return std::make_pair(label, position);
        }
        return std::make_pair(static_cast<Command>(number_of_commands), -1);
    }

    std::pair<Command, int> extractCommandCode(char *in) {
        size_t command;
        int position = 0;
        sscanf(in, "%d%n", &command, &position);
        return std::make_pair(static_cast<Command>(command), position);
    }

    std::pair<Command, int> extractCommandByte(char *in) {
        char command = in[0];
        int position = 1;
        return std::make_pair(static_cast<Command>(command), position);
    }

    std::pair<TypeOfMemory, int> getTypeOfMemory(char *in) {
        switch (in[0]) {
            case 'r': {
                return std::make_pair(static_cast<TypeOfMemory >(RAX + (in[1] - 'a')), 3);
            }
            case '[': {
                return std::make_pair(RAM, 1);
            }
            default:{
                return std::make_pair(STACK, 0);
            }
        }
    }
}