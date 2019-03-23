//
// Created by user on 14.10.18.
//

#include "ByteToCodeConverter.h"

#include <fstream>
#include <cstring>
#include <iostream>
#include "../../CommandService/CommandService.h"
#include "../CodeToByteConverter/CodeToByteConverter.h"
#define MAX_LINE_SIZE 256

namespace ByteToCodeConverter {

    ErrorCode convert(char *program, char *filename, int length) {


        std::map<int, std::string> dataVal;
        std::map<int, int> dataPos;

        std::map<int, int> labels = getLabels(program, length, dataVal, dataPos);
        std::ofstream myfile;
        myfile.open(filename);

        if (getNumber(program) != CodeToByteConverter::version) {
            return ErrorCode::FAIL;
        }

        int currentPosition = 4;
        int currentLine = 0;

        while (currentPosition < length) {
            auto command = std::make_pair(CommandService::Command::no_such_command, 0);
            command = CommandService::extractCommandByte(program + currentPosition);
            if (command.first != CommandService::Command::data && command.first != CommandService::Command::end) {
                myfile << command.first;
            }
            if (command.first == CommandService::Command::end ||
                command.first == CommandService::Command::no_such_command) {
                if (command.first == CommandService::Command::end) {
                    writeData(myfile, dataVal, dataPos);

                    myfile << command.first << std::endl;
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
                case CommandService::Command::pop : {
                }
                case CommandService::Command::push : {

                    int length_to_read = getNumber(program + currentPosition);
                    currentPosition += 4;

                    auto pushPopString = CommandService::extractWord(program + currentPosition, length_to_read);
                    currentPosition += length_to_read;

                    myfile << " " << pushPopString.first;
                    break;
                }
                case CommandService::Command::jmp : {
                }
                case CommandService::Command::call : {
                }
                case CommandService::Command::print : {
                    //  std::string number = CommandService::extractWord(program + currentPosition, 4).first;
                    int positionToJump = getNumber(program + currentPosition);
                    myfile << " " << dataPos[positionToJump];
                    currentPosition += 4;
                    break;
                }
                case CommandService::Command::je : {
                }
                case CommandService::Command::ja : {
                  //  std::string number = CommandService::extractWord(program + currentPosition, 4).first;
                    int positionToJump = getNumber(program + currentPosition);
                    myfile << " " << labels[positionToJump];
                    currentPosition += 4;
                    break;
                }
                case CommandService::Command::data : {
                    skipData(program, currentPosition, dataVal, dataPos);
                    break;
                }
            }


            if (command.first != CommandService::Command::data && command.first != CommandService::Command::end) {

                myfile << std::endl;
            }

            currentLine++;

        }
        myfile << "--- NO ENDING -----";
        myfile.close();
        return FAIL;
    }

    std::map<int, int>  getLabels(char* program, int length, std::map<int, std::string> &dataVal, std::map<int, int> &dataPos){
        std::map<int, int> labels;
        int currentPosition = 4;
        int currentLine = 0;
        while (currentPosition != length) {
            labels[currentPosition] = currentLine;
            auto command = std::make_pair(CommandService::Command::no_such_command, 0);
            command = CommandService::extractCommandByte(program + currentPosition);
            if (command.first == CommandService::Command::end ||
                command.first == CommandService::Command::no_such_command) {
                break;
            }



            currentPosition += command.second;


            switch (command.first) {
                case CommandService::Command::pop : {
                }
                case CommandService::Command::push : {
                    int length_of_command = getNumber(program + currentPosition);
                    currentPosition += 4;
                    currentPosition += length_of_command;
                    break;
                }
                case CommandService::Command::print : {

                }
                case CommandService::Command::jmp : {
                }
                case CommandService::Command::call : {
                }
                case CommandService::Command::je : {
                }
                case CommandService::Command::ja : {
                    currentPosition += 4;
                    break;
                }
                case CommandService::Command::data : {
                    skipData(program, currentPosition, dataVal, dataPos);
                    break;
                }
            }

            currentLine++;
        }

        return labels;
    }

    int getNumber(char *strin) {
        return int((unsigned char)(strin[0]) |
                   (unsigned char)(strin[1]) << 8 |
                   (unsigned char)(strin[2]) << 16 |
                   (unsigned char)(strin[3]) << 24);
    }

    void writeData(std::ofstream &out, std::map<int, std::string> &dataVal, std::map<int, int> &dataPos) {
        if (dataVal.size() == 0) {
            return;
        }

        out << static_cast<int>(CommandService::Command::data) << std::endl;
        std::map<int, std::string> indexToString;

        int maxIndex = dataVal.size() + 1;

        for (int i = 1; i < maxIndex; i++) {
            out << i << " \""  << dataVal[i] << "\"" << std::endl;
        }


    }

    void skipData(char *program, int &currentPosition, std::map<int, std::string> &dataVal, std::map<int, int> &dataPos) {

        bool toAddData = dataVal.size() <= 0;
        int count = 0;

        char varName[MAX_LINE_SIZE];
        int sum = 0;

        for (; program[currentPosition] != '\0'; ) {

            if (program[currentPosition] == '.') {
                break;
            }


            auto pushPopString = CommandService::extractWordByte(program + currentPosition);
            currentPosition += pushPopString.second;


            if (toAddData) {
                dataPos[sum] = ++count;
                dataVal[count] = pushPopString.first;
                sum += pushPopString.first.length() + 1;
            }
            currentPosition++;
        }
        currentPosition += 1;
    }
}
