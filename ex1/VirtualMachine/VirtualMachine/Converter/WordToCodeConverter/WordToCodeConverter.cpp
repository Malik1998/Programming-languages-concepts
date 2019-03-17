//
// Created by user on 13.10.18.
//

#include <ostream>
#include <map>
#include <iostream>
#include "cstring"
#include "WordToCodeConverter.h"
#define MAX_LINE_SIZE 256
#define FILE_NAME CODE_COMMANDS

namespace WordToCodeConverter {
    ErrorCode convert(char *program, char *filename) {

        std::map<std::string, int> labels = getLabels(program);
        std::ofstream myfile;
        myfile.open(filename);
        int currentPosition = 0;
        int currentLine = 0;
        while (currentPosition != std::strlen(program)) {
            auto command = std::make_pair(CommandService::Command::no_such_command, 0);
            command = CommandService::extractCommandWord(program + currentPosition);
            if (command.first == CommandService::Command::end ||
                command.first == CommandService::Command::no_such_command) {
                if (command.first == CommandService::Command::end) {
                    myfile << static_cast<int>(command.first);
                    myfile.close();
                    return OK;
                } else {
                    myfile << "---- UNKNOWN COMMAND --------" << std::endl;
                    myfile.close();
                    return FAIL;
                }
            }

            currentPosition += command.second;

            if (command.first != CommandService::Command::label) {
                myfile << static_cast<int>(command.first);
            }

            switch (command.first) {
                case CommandService::Command::print : {
                    auto pushPopString = CommandService::extractWord(program + currentPosition);
                    currentPosition += pushPopString.second;

                    myfile << " " << "\"" << pushPopString.first << "\"";
                    break;
                }
                case CommandService::Command::pop : {
                }
                case CommandService::Command::push : {
                    auto pushPopString = CommandService::extractWord(program + currentPosition);
                    currentPosition += pushPopString.second;

                    myfile << " " << pushPopString.first;
                    break;
                }
                case CommandService::Command::label : {
                    auto labelName = CommandService::extractWord(program + currentPosition);
                    currentLine--;
                    break;
                }
                case CommandService::Command::jmp : {
                }
                case CommandService::Command::call : {
                }
                case CommandService::Command::je : {
                }
                case CommandService::Command::ja : {
                    auto labelName = CommandService::extractWord(program + currentPosition);
                    currentPosition += labelName.second;
                    myfile << " " << labels[labelName.first];
                    break;
                }
            }

            currentLine++;
            if (command.first != CommandService::Command::label) {
                myfile << std::endl;
            }

        }
        myfile << "--- NO ENDING -----" << std::endl;
        myfile.close();
        return FAIL;
    }

    std::map<std::string, int>  getLabels(char* program) {
        std::map<std::string, int> labels;
        int currentPosition = 0;
        int currentLine = 0;
        int countLabels = 0;
        while (currentPosition != std::strlen(program)) {
            auto command = std::make_pair(CommandService::Command::no_such_command, 0);
            command = CommandService::extractCommandWord(program + currentPosition);
            if (command.first == CommandService::Command::end ||
                command.first == CommandService::Command::no_such_command) {
                break;
            }

            currentPosition += command.second;

            switch (command.first) {

                case CommandService::Command::print : {

                }
                case CommandService::Command::pop : {
                }
                case CommandService::Command::push : {
                    auto pushPopString = CommandService::extractWord(program + currentPosition);
                    currentPosition += pushPopString.second;
                    break;
                }
                case CommandService::Command::label : {
                    std::string labelName = CommandService::extractWord(program + currentPosition - command.second).first;
                    labels[labelName.substr(0, labelName.length() - 1)] = currentLine - countLabels; // cause it's look like: 'label_name: '
                    countLabels++;
                    break;
                }
                case CommandService::Command::jmp : {
                }
                case CommandService::Command::call : {
                }
                case CommandService::Command::je : {
                }
                case CommandService::Command::ja : {
                    auto labelName = CommandService::extractWord(program + currentPosition);
                    currentPosition += labelName.second;
                    break;
                }
            }

            currentLine++;
        }

        return labels;
    }
}
