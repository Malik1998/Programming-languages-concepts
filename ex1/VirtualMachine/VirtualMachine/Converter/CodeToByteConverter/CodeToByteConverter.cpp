//
// Created by user on 14.10.18.
//

#include <fstream>
#include <cstring>
#include <iostream>
#include "CodeToByteConverter.h"
#include "../../CommandService/CommandService.h"
#define MAX_LINE_SIZE 256

namespace CodeToByteConverter {

    ErrorCode convert(char *program, char *filename) {

        std::map<int, std::string> dataVal;
        std::map<int, int> dataPos;

        std::map<int, int> labels = getLabels(program, dataVal, dataPos);
        std::ofstream myfile;
        myfile.open(filename, std::ios::binary | std::ios::out);
        int currentPosition = 0;
        int currentLine = 0;
        myfile.write(reinterpret_cast<const char *>(&version), sizeof(version));
        while (currentPosition != std::strlen(program)) {
            auto command = std::make_pair(CommandService::Command::no_such_command, 0);
            command = CommandService::extractCommandCode(program + currentPosition);
            char encodedCommand = static_cast<char>(command.first);
            if (command.first != CommandService::Command::data && command.first != CommandService::Command::end) {
                myfile.write(&encodedCommand, sizeof(encodedCommand));
            }
            if (command.first == CommandService::Command::end ||
                command.first == CommandService::Command::no_such_command) {
                if (command.first == CommandService::Command::end) {
                    writeData(myfile, dataVal, dataPos);
                    char encodedCommand = static_cast<char>(CommandService::Command::end);
                    myfile.write(&encodedCommand , sizeof(encodedCommand));
                    myfile.close();
                    return OK;
                } else {
                    myfile << "---- UNKNOWN COMMAND --------";
                    myfile.close();
                    return FAIL;
                }
            }

            currentPosition += command.second;

            switch (command.first) {
                case CommandService::Command::print : {
                    auto labelName = CommandService::extractWord(program + currentPosition);
                    currentPosition += labelName.second;
                    unsigned int labelPointer = static_cast<unsigned int>(dataPos[std::stoi(labelName.first)]);

                    myfile.write(reinterpret_cast<const char *>(&labelPointer), sizeof(labelPointer));
                    break;
                }
                case CommandService::Command::pop : {
                }
                case CommandService::Command::push : {
                    auto pushPopString = CommandService::extractWord(program + currentPosition);
                    currentPosition += pushPopString.second;
                    unsigned int length = static_cast<int>(pushPopString.first.length());
                    myfile.write(reinterpret_cast<const char *>(&length), sizeof(length));
                    myfile.write((pushPopString.first.c_str()), length);
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
                    unsigned int labelPointer = static_cast<unsigned int>(labels[std::stoi(labelName.first)]);

                    myfile.write(reinterpret_cast<const char *>(&labelPointer), sizeof(labelPointer));
                    break;
                }
                case CommandService::Command::data : {
                    skipData(program, currentPosition, currentLine, dataVal, dataPos);
                    break;
                }
            }
            currentLine++;
        }
        myfile << "--- NO ENDING -----";
        myfile.close();
        return FAIL;
    }

    std::map<int, int>  getLabels(char* program, std::map<int, std::string> &dataVal, std::map<int, int> &dataPos) {
        std::map<int, int> labels;
        int currentPosition = 0;
        int pos = 4;
        int currentLine = 0;
        while (currentPosition != std::strlen(program)) {
            labels[currentLine] = pos;
            auto command = std::make_pair(CommandService::Command::no_such_command, 0);
            command = CommandService::extractCommandCode(program + currentPosition);
            if (command.first == CommandService::Command::end ||
                command.first == CommandService::Command::no_such_command) {
                break;
            }

            pos++;
            currentPosition += command.second;

            switch (command.first) {
                case CommandService::Command::pop : {
                }
                case CommandService::Command::push : {
                    auto pushPopString = CommandService::extractWord(program + currentPosition);
                    pos += 4 + (int)(pushPopString.first.length());
                    currentPosition += pushPopString.second;
                    break;
                }
                case CommandService::Command::jmp : {
                }
                case CommandService::Command::call : {
                }
                case CommandService::Command::je : {
                }
                case CommandService::Command::print : {

                }
                case CommandService::Command::ja : {
                    auto labelName = CommandService::extractWord(program + currentPosition);
                    currentPosition += labelName.second;
                    pos += 4;
                    break;
                }
                case CommandService::Command::data : {
                    skipData(program, currentPosition, currentLine, dataVal, dataPos);
                    break;
                }
            }

            currentLine++;
        }

        return labels;
    }

    void writeData(std::ofstream &out, std::map<int, std::string> &dataVal, std::map<int, int> &dataPos) {
        if (dataVal.size() == 0) {
            return;
        }

        char encodedCommand = static_cast<char>(CommandService::Command::data);
        out.write(&encodedCommand , sizeof(encodedCommand));
        std::map<int, std::string> indexToString;

        int maxIndex = dataVal.size();

        for (int i = 1; i <= maxIndex; i++) {
            out.write(dataVal[i].c_str() , dataVal[i].length());
            char c = '\0';
            out.write(&c, 1);
        }
        char c = '.';
        out.write(&c, 1);
    }

    void skipData(char *program, int &currentPosition, int &currentLine, std::map<int, std::string> &dataVal, std::map<int, int> &dataPos) {

        bool toAddData = dataVal.size() <= 0;
        int count = 0;

        char varName[MAX_LINE_SIZE];

        int sum = 0;

        for (; program[currentPosition] != '\0'; ) {

            int position;
            sscanf(program + currentPosition, "%s%n", varName, &position);

            if (program[currentPosition + position + 1] != '\"') {
                break;
            }

            currentPosition += position;

            auto pushPopString = CommandService::extractWord(program + currentPosition);
            currentPosition += pushPopString.second;


            if (toAddData) {
                dataPos[++count] = sum;
                dataVal[count] = pushPopString.first;
                sum += pushPopString.first.length() + 1;
            }
            currentLine++;
        }
    }

}
