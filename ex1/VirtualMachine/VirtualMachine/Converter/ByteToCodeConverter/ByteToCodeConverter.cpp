//
// Created by user on 14.10.18.
//

#include "ByteToCodeConverter.h"

#include <fstream>
#include <cstring>
#include <iostream>
#include "../../CommandService/CommandService.h"
#include "../CodeToByteConverter/CodeToByteConverter.h"

namespace ByteToCodeConverter {

    ErrorCode convert(char *program, char *filename, int length) {


        std::map<int, int> labels = getLabels(program, length);
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
            myfile << command.first;
            if (command.first == CommandService::Command::end ||
                command.first == CommandService::Command::no_such_command) {
                if (command.first == CommandService::Command::end) {
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

                    int length_to_read = getNumber(program + currentPosition);
                    currentPosition += 4;

                    auto pushPopString = CommandService::extractWord(program + currentPosition, length_to_read);
                    currentPosition += length_to_read;

                    myfile << " " << "\"" << pushPopString.first << "\"";
                    break;

                }
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
                case CommandService::Command::je : {
                }
                case CommandService::Command::ja : {
                  //  std::string number = CommandService::extractWord(program + currentPosition, 4).first;
                    int positionToJump = getNumber(program + currentPosition);
                    myfile << " " << labels[positionToJump];
                    currentPosition += 4;
                    break;
                }
            }




            myfile << std::endl;

            currentLine++;

        }
        myfile << "--- NO ENDING -----";
        myfile.close();
        return FAIL;
    }

    std::map<int, int>  getLabels(char* program, int length) {
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
                case CommandService::Command::print : {

                }
                case CommandService::Command::pop : {
                }
                case CommandService::Command::push : {
                    int length_of_command = getNumber(program + currentPosition);
                    currentPosition += 4;
                    currentPosition += length_of_command;
                    break;
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
}
