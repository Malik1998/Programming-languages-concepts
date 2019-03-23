//
// Created by user on 13.10.18.
//

#include <ostream>
#include <map>
#include <math.h>
#include <iostream>
#include "cstring"
#include "WordToCodeConverter.h"
#define MAX_LINE_SIZE 256
#define FILE_NAME CODE_COMMANDS

namespace WordToCodeConverter {
    ErrorCode convert(char *program, char *filename) {

        std::map<std::string, int> data;
        std::map<int, std::string> dataVal;
        std::map<std::string, int> labels = getLabels(program, data, dataVal);
        std::ofstream myfile;
        myfile.open(filename);
        int currentPosition = 0;


        while (currentPosition != std::strlen(program)) {
            auto command = std::make_pair(CommandService::Command::no_such_command, 0);
            command = CommandService::extractCommandWord(program + currentPosition);
            if (command.first == CommandService::Command::end ||
                command.first == CommandService::Command::no_such_command) {
                if (command.first == CommandService::Command::end) {

                    writeData(myfile, data, dataVal);

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

            if (command.first != CommandService::Command::label && command.first != CommandService::Command::data) {
                myfile << static_cast<int>(command.first);
            }

            switch (command.first) {
                case CommandService::Command::print : {
                    auto pushPopString = CommandService::extractWord(program + currentPosition);
                    currentPosition += pushPopString.second;

                    myfile << " " << data[pushPopString.first];
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
                case CommandService::Command::data : {
                    skipData(program, currentPosition, data, dataVal);
                    break;
                }
            }

            if (command.first != CommandService::Command::label && command.first != CommandService::Command::data) {
                myfile << std::endl;
            }

        }
        myfile << "--- NO ENDING -----" << std::endl;
        myfile.close();
        return FAIL;
    }

    std::map<std::string, int>  getLabels(char* program, std::map<std::string, int>& data, std::map<int, std::string>& dataVal) {
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
                case CommandService::Command::data : {
                    skipData(program, currentPosition, data, dataVal);
                    break;
                }
            }

            currentLine++;
        }

        return labels;
    }

    void writeData(std::ofstream &out, std::map<std::string, int> &data, std::map<int, std::string> &dataVal) {
        if (data.size() == 0) {
            return;
        }

        out << static_cast<int>(CommandService::Command::data) << std::endl;
        std::map<int, std::string> indexToString;

        int maxIndex = 0;
        for(auto& kv: data) {
            indexToString[kv.second] = kv.first;
            maxIndex = std::max(kv.second, maxIndex);
        }

        for (int i = 1; i <= maxIndex; i++) {
            out << i << " \""  << dataVal[i] << "\"" << std::endl;
        }


    }

    void skipData(char *program, int &currentPosition, std::map<std::string, int> &data, std::map<int, std::string> &dataVal) {

        bool toAddData = data.size() <= 0;
        int count = 0;

        char varName[MAX_LINE_SIZE];

        for (; program[currentPosition] != '\0'; ) {

            int position;
            sscanf(program + currentPosition, "%s%n", varName, &position);

            if (varName[0] != '.' || position <= 0) {
                break;
            }

            currentPosition += position;

            auto pushPopString = CommandService::extractWord(program + currentPosition);
            currentPosition += pushPopString.second;


            if (toAddData) {
                data[std::string(varName)] = ++count;
                dataVal[count] = pushPopString.first;
            }
        }
    }
}
