//
// Created by user on 14.10.18.
//

#include <cstdio>
#include <fstream>
#include <cstring>
#include "CodeToWordConverter.h"
#include "../../CommandService/CommandService.h"
#define MAX_LINE_SIZE 256


namespace CodeToWordConverter {
using namespace CommandService;

    ErrorCode convert(char *program, char *filename) {

        std::map<int, std::string> dataVal;
        std::map<int, int> labels = getLabels(program, dataVal);
        std::ofstream myfile;
        myfile.open(filename);
        int currentPosition = 0;
        int currentLine = 0;
        while (currentPosition != std::strlen(program)) {
            auto command = std::make_pair(CommandService::Command::no_such_command, 0);
            command = CommandService::extractCommandCode(program + currentPosition);
            if (labels.find(static_cast<const int &>(currentLine)) != labels.end()) {
                myfile << labels[static_cast<const int &>(currentLine)] << ":" << std::endl;
            }
            if (command.first == CommandService::Command::end ||
                command.first == CommandService::Command::no_such_command) {
                if (command.first == CommandService::Command::end) {

                    writeData(myfile, dataVal);
                    myfile << commands[static_cast<int>(command.first)] << std::endl;
                    myfile.close();
                    return OK;
                } else {
                    myfile << "---- UNKNOWN COMMAND --------" << std::endl;
                    myfile.close();
                    return FAIL;
                }
            }

            currentPosition += command.second;

            if (command.first != CommandService::Command::data) {
                myfile << commands[static_cast<int>(command.first)];
            }

            switch (command.first) {
                case CommandService::Command::print : {
                    auto pushPopString = CommandService::extractWord(program + currentPosition);
                    currentPosition += pushPopString.second;
                    myfile << " " << "." <<pushPopString.first;
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
                case CommandService::Command::jmp : {
                }
                case CommandService::Command::call : {
                }
                case CommandService::Command::je : {
                }
                case CommandService::Command::ja : {
                    auto labelName = CommandService::extractWord(program + currentPosition);
                    currentPosition += labelName.second;
                    myfile << " " << labels[std::stoi(labelName.first)];
                    break;
                }
                case CommandService::Command::data : {
                    skipData(program, currentPosition, dataVal);
                    break;
                }
            }

            currentLine++;

            if (command.first != CommandService::Command::data) {
                myfile << std::endl;
            }

        }
        myfile << "--- NO ENDING -----" << std::endl;
        myfile.close();
        return FAIL;
    }

    std::map<int, int>  getLabels(char* program, std::map<int, std::string>& dataVal) {
        std::map<int, int> labels;
        int currentPosition = 0;
        int currentLine = 0;
        while (currentPosition != std::strlen(program)) {
            auto command = std::make_pair(CommandService::Command::no_such_command, 0);
            command = CommandService::extractCommandCode(program + currentPosition);
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
                case CommandService::Command::jmp : {
                }
                case CommandService::Command::call : {
                }
                case CommandService::Command::je : {
                }
                case CommandService::Command::ja : {
                    auto labelName = CommandService::extractWord(program + currentPosition);
                    currentPosition += labelName.second;
                    labels[std::stoi(labelName.first)] = 1;
                    break;
                }
                case CommandService::Command::data : {
                    skipData(program, currentPosition, dataVal);
                    break;
                }
            }

            currentLine++;
        }

        currentPosition = 0;
        currentLine = 0;
        int currentLine1 = 0;
        while (currentPosition != std::strlen(program)) {
            auto command = std::make_pair(CommandService::Command::no_such_command, 0);
            command = CommandService::extractCommandCode(program + currentPosition);
            if (labels.find(static_cast<const int &>(currentLine)) != labels.end()) {
                labels[currentLine] = currentLine1;
                currentLine1++;
            }
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
                case CommandService::Command::jmp : {

                }
                case CommandService::Command::je : {
                }
                case CommandService::Command::ja : {
                    auto labelName = CommandService::extractWord(program + currentPosition);
                    currentPosition += labelName.second;
                    break;
                }
                case CommandService::Command::data : {
                    skipData(program, currentPosition, dataVal);
                    break;
                }
            }

            currentLine++;
            currentLine1++;
        }


        return labels;
    }

    void writeData(std::ofstream &out, std::map<int, std::string> &dataVal) {
        if (dataVal.size() == 0) {
            return;
        }

        out << commands[static_cast<int>(CommandService::Command::data)] << std::endl;

        int maxIndex = dataVal.size() + 1;

        for (int i = 1; i < maxIndex; i++) {
            out << "." << i << " \""  << dataVal[i] << "\"" << std::endl;
        }


    }

    void skipData(char *program, int &currentPosition, std::map<int, std::string> &dataVal) {

        bool toAddData = dataVal.size() <= 0;
        int count = 0;

        char varName[MAX_LINE_SIZE];

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
                dataVal[++count] = pushPopString.first;
            }
        }
    }

};